main:
addi $gp $sp 0
addi $sp $sp -12
addi $fp $sp 0
addi $sp $sp -8
addi $t1 $0 0
addi $t0 $t1 50
sw $t0 4($sp)
j label0
label1:
lw $t0 0($s0)
addi $s0 $s0 4
sw $t0 0($sp)
j label2
label2:
addi $v0 $0 5
syscall
addi $s1 $sp 0
sw $v0 0($s1)
lw $t0 -4($gp)
sw $t0 8($fp)
lw $t0 -8($gp)
sw $t0 4($fp)
lw $t0 -12($gp)
sw $t0 0($fp)
lw $sp -8($fp)
lw $s2 -12($fp)
lw $gp -16($fp)
lw $fp -20($fp)
jr $ra
label0:
addi $s3 $sp 0
addi $s4 $fp 0
lw $t0 -4($gp)
sw $t0 -4($sp)
lw $t0 -8($gp)
sw $t0 -8($sp)
lw $t0 -12($gp)
sw $t0 -12($sp)
sw $sp -16($sp)
sw $sp -20($sp)
sw $ra -24($sp)
sw $gp -28($sp)
sw $fp -32($sp)
addi $gp $sp 0
addi $sp $sp -12
addi $fp $sp 0
addi $sp $sp -24
addi $s0 $sp 0
addi $t0 $s3 0
addi $s0 $s0 -4
sw $t0 0($s0)
jal label1
addi $ra $s2 0
lw $t1 4($sp)
addi $t0 $t1 0
sw $t0 -4($gp)
addi $t1 $0 0
addi $t0 $t1 1
sw $t0 -8($gp)
lw $t1 -4($gp)
lw $t2 -8($gp)
add $t0 $t1 $t2
sw $t0 -8($gp)
lw $t1 -8($gp)
addi $t0 $t1 0
sw $t0 0($sp)
addi $v0 $0 4
la $a0 str0
syscall
lw $t1 0($sp)
addi $t0 $t1 0
sw $t0 -12($gp)
addi $v0 $0 1
lw $a0 -12($gp)
syscall
jr $ra
.data
str0:.asciiz"h is"
