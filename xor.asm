format ELF64

public encrypt_db


section ".text" executable


encrypt_db:
    




.loop:
    test rsi, rsi
    jz .done

    mov al, byte [rdi]
    xor al, dl
    mov byte [rdi], al

    inc rdi
    dec rsi
    jmp .loop





.done:
    ret