<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class SameBoxChat
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing AndAlso components IsNot Nothing Then
            components.Dispose()
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.Label1 = New System.Windows.Forms.Label
        Me.tbxConversation = New System.Windows.Forms.TextBox
        Me.btnSend = New System.Windows.Forms.Button
        Me.tbxMessage = New System.Windows.Forms.TextBox
        Me.Label2 = New System.Windows.Forms.Label
        Me.Label3 = New System.Windows.Forms.Label
        Me.tbxStatus = New System.Windows.Forms.TextBox
        Me.SuspendLayout()
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.Location = New System.Drawing.Point(13, 13)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(99, 16)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "Conversation"
        '
        'tbxConversation
        '
        Me.tbxConversation.Location = New System.Drawing.Point(16, 33)
        Me.tbxConversation.Multiline = True
        Me.tbxConversation.Name = "tbxConversation"
        Me.tbxConversation.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.tbxConversation.Size = New System.Drawing.Size(764, 288)
        Me.tbxConversation.TabIndex = 1
        '
        'btnSend
        '
        Me.btnSend.Location = New System.Drawing.Point(16, 359)
        Me.btnSend.Name = "btnSend"
        Me.btnSend.Size = New System.Drawing.Size(75, 23)
        Me.btnSend.TabIndex = 2
        Me.btnSend.Text = "Send"
        Me.btnSend.UseVisualStyleBackColor = True
        '
        'tbxMessage
        '
        Me.tbxMessage.Location = New System.Drawing.Point(98, 342)
        Me.tbxMessage.Multiline = True
        Me.tbxMessage.Name = "tbxMessage"
        Me.tbxMessage.Size = New System.Drawing.Size(682, 56)
        Me.tbxMessage.TabIndex = 3
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label2.Location = New System.Drawing.Point(12, 327)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(72, 16)
        Me.Label2.TabIndex = 4
        Me.Label2.Text = "Message"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label3.Location = New System.Drawing.Point(16, 409)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(51, 16)
        Me.Label3.TabIndex = 5
        Me.Label3.Text = "Status"
        '
        'tbxStatus
        '
        Me.tbxStatus.Location = New System.Drawing.Point(19, 428)
        Me.tbxStatus.Multiline = True
        Me.tbxStatus.Name = "tbxStatus"
        Me.tbxStatus.ReadOnly = True
        Me.tbxStatus.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.tbxStatus.Size = New System.Drawing.Size(761, 132)
        Me.tbxStatus.TabIndex = 6
        '
        'SameBoxChat
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(8.0!, 16.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(792, 572)
        Me.Controls.Add(Me.tbxStatus)
        Me.Controls.Add(Me.Label3)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.tbxMessage)
        Me.Controls.Add(Me.btnSend)
        Me.Controls.Add(Me.tbxConversation)
        Me.Controls.Add(Me.Label1)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Margin = New System.Windows.Forms.Padding(4)
        Me.Name = "SameBoxChat"
        Me.Text = "SameBoxChat Demo"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents tbxConversation As System.Windows.Forms.TextBox
    Friend WithEvents btnSend As System.Windows.Forms.Button
    Friend WithEvents tbxMessage As System.Windows.Forms.TextBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents tbxStatus As System.Windows.Forms.TextBox

End Class
