Imports System.Runtime.InteropServices

Public Class SameBoxChat
    Private Const WM_COPYDATA As Integer = &H4A
    Private Const WindowName As String = "Receive WM_COPYDATA"

    <StructLayout(LayoutKind.Sequential)> _
       Private Structure CopyData
        Public dwData As IntPtr
        Public cbData As Integer
        Public lpData As IntPtr
    End Structure

    Private Declare Auto Function SendMessage Lib "user32" (ByVal hWnd As IntPtr, ByVal Msg As Integer, ByVal wParam As IntPtr, ByRef lParam As CopyData) As Boolean

    Protected Overrides Sub WndProc(ByRef m As Message)
        If m.Msg = WM_COPYDATA Then
            Dim data As CopyData
            Dim message As String
            data = CType(m.GetLParam(GetType(CopyData)), CopyData)
            DumpCopyData(data)
            message = Marshal.PtrToStringAuto(data.lpData, data.cbData \ Marshal.SystemDefaultCharSize)
            Me.tbxConversation.Text &= data.dwData.ToString & " " & DateTime.Now.ToShortTimeString() & ": " & message & vbCrLf
            m.Result = New IntPtr(1)
        Else
            MyBase.WndProc(m)
        End If
    End Sub

    Private Sub btnSend_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnSend.Click
        Dim proc As Process = Process.GetCurrentProcess()
        Dim processes() As Process = Process.GetProcessesByName(proc.ProcessName)

        If processes.Length > 1 And Me.tbxMessage.Text.Length > 0 Then
            For Each p As Process In processes
                If p.Id <> proc.Id Then
                    Dim message As String = Me.tbxMessage.Text
                    Dim data As CopyData
                    data.dwData = proc.Id
                    data.lpData = Marshal.StringToHGlobalAuto(message)
                    data.cbData = message.Length * Marshal.SystemDefaultCharSize
                    DumpCopyData(data)
                    SendMessage(p.MainWindowHandle, WM_COPYDATA, p.Handle, data)
                    Marshal.FreeHGlobal(data.lpData)

                    Me.tbxConversation.Text &= proc.Id.ToString & " " & DateTime.Now.ToShortTimeString() & ": " & Me.tbxMessage.Text & vbCrLf
                    Me.tbxMessage.Clear()
                End If
            Next
        Else
            MessageBox.Show("No other running applications found.")
        End If
    End Sub

#Region "Debug Display Functions"

    Private Sub SameBoxChat_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Me.tbxStatus.Text &= "Process ID is " & Process.GetCurrentProcess.Id.ToString & vbCrLf
    End Sub

    Private Sub DumpCopyData(ByRef cd As CopyData)
        Me.tbxStatus.Text &= "Dump CopyData struct" & vbCrLf
        Me.tbxStatus.Text &= "    dwData (Sending process id): " & cd.dwData.ToString & vbCrLf
        Me.tbxStatus.Text &= "    lpData (Pointer to string): " & cd.lpData.ToString() & vbCrLf
        Me.tbxStatus.Text &= "    cbData (Length of string): " & cd.cbData.ToString() & vbCrLf
        Me.tbxStatus.Text &= "    String: " & Marshal.PtrToStringAuto(cd.lpData, cd.cbData \ Marshal.SystemDefaultCharSize) & vbCrLf
    End Sub
#End Region

End Class
