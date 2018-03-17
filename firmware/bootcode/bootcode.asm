org 7C00h

boot_jump:
  jmp short boot_main
  nop
filesystem_header:
  times 59 db 0
boot_main:
prepare_to_display_string:
  xor ax, ax
  mov ds, ax
  mov si, string
display_string_loop:
  lodsb
  test al, al
  jz wait_for_key_press
  mov ah, 0Eh
  mov bx, 0007h
  int 10h
  jmp short display_string_loop
wait_for_key_press:
  xor ah, ah
  int 16h
reboot:
  int 19h
halt_if_all_else_fails:
  hlt
  jmp short halt_if_all_else_fails

string:
  db "The tape punch interface is not a bootable device.", 0xD, 0xA
  db 0xD, 0xA
  db "If this happened automatically, please unplug the tape punch interface while", 0xD, 0xA
  db "starting up your computer, or configure your computer's BIOS to prevent this", 0xD, 0xA
  db "behaviour.", 0xD, 0xA
  db 0xD, 0xA
  db "Press any key to continue.", 0xD, 0xA, 0x0
