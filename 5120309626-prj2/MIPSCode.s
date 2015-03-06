	.data
a_global:
	.space 400
	.text
	.data
v_global:
	.space 400
	.text
	.data
c_global:
	.space 400
	.text
	.data
b_global:
	.space 400
	.text
	.data
s_global: .word 0
	.text
	.data
n_global: .word 0
	.text

print_global:
	li $t0, 12
	sub $sp, $sp, $t0
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	li $t0, 1
	addi $t1, $sp, 8
	sw $t0, 0($t1)

print_global_for_cond_a:
	addi $t0, $sp, 8
	lw $t0, 0($t0)
	la $t1, n_global
	lw $t1, 0($t1)
	slt $t2, $t0, $t1
	beq $t2, $zero, print_global_for_end_a
	add $t0, $zero, $zero
	addi $t2, $sp, 8
	lw $t2, 0($t2)
	li $t1, 100
	mul $t0, $t0, $t1
	add $t0, $t0, $t2
	li $t1, 4
	mul $t0, $t0, $t1
	la $t1, b_global
	add $t0, $t1, $t0
	lw $t0, 0($t0)
	add $a1, $v0, $zero
	add $a2, $a0, $zero
	li $v0, 1
	add $a0, $t0, $zero
	syscall
	add $v0, $a1, $zero
	add $a0, $a2, $zero

print_global_for_incr_a:
	addi $t0, $sp, 8
	lw $t1, 0($t0)
	addi $t1, $t1, 1
	sw $t1, 0($t0)
	j print_global_for_cond_a

print_global_for_end_a:
	add $t0, $zero, $zero
	la $t2, n_global
	lw $t2, 0($t2)
	li $t1, 100
	mul $t0, $t0, $t1
	add $t0, $t0, $t2
	li $t1, 4
	mul $t0, $t0, $t1
	la $t1, b_global
	add $t0, $t1, $t0
	lw $t0, 0($t0)
	add $a1, $v0, $zero
	add $a2, $a0, $zero
	li $v0, 1
	add $a0, $t0, $zero
	syscall
	add $v0, $a1, $zero
	add $a0, $a2, $zero
	li $t0, 0
	add $v0, $t0, $zero
	j print_global_end

print_global_end:
	lw $ra, 0($sp)
	addi $sp, $sp, 12
	jr $ra

DFS_global:
	li $t0, 24
	sub $sp, $sp, $t0
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	addi $t0, $a0, 0
	lw $t0, 0($t0)
	la $t1, n_global
	lw $t1, 0($t1)
	sgt $t2, $t0, $t1
	beq $t2, $zero, DFS_global_endif_a
	la $t0, s_global
	lw $t0, 0($t0)
	li $t1, 3
	slt $t2, $t0, $t1
	beq $t2, $zero, DFS_global_endif_b
	addi $a0, $sp, 20
	jal print_global
	add $t0, $v0, $zero
	lw $a0, 4($sp)

DFS_global_endif_b:
	la $t0, s_global
	lw $t1, 0($t0)
	addi $t1, $t1, 1
	sw $t1, 0($t0)
	li $t0, 0
	add $v0, $t0, $zero
	j DFS_global_end

DFS_global_endif_a:
	li $t0, 1
	addi $t1, $sp, 8
	sw $t0, 0($t1)

DFS_global_for_cond_c:
	addi $t0, $sp, 8
	lw $t0, 0($t0)
	la $t1, n_global
	lw $t1, 0($t1)
	li $t2, 1
	add $t3, $t1, $t2
	slt $t1, $t0, $t3
	beq $t1, $zero, DFS_global_for_end_c
	add $t0, $zero, $zero
	addi $t2, $sp, 8
	lw $t2, 0($t2)
	li $t1, 100
	mul $t0, $t0, $t1
	add $t0, $t0, $t2
	li $t1, 4
	mul $t0, $t0, $t1
	la $t1, a_global
	add $t0, $t1, $t0
	lw $t0, 0($t0)
	seq $t0, $zero, $t0
	add $t1, $t0, $zero
	beq $t0, $zero, DFS_global_shortcircuit_e
	add $t2, $zero, $zero
	addi $t4, $sp, 8
	lw $t4, 0($t4)
	addi $t5, $a0, 0
	lw $t5, 0($t5)
	add $t6, $t4, $t5
	li $t3, 100
	mul $t2, $t2, $t3
	add $t2, $t2, $t6
	li $t3, 4
	mul $t2, $t2, $t3
	la $t3, v_global
	add $t2, $t3, $t2
	lw $t2, 0($t2)
	seq $t2, $zero, $t2
	add $t1, $t2, $zero

DFS_global_shortcircuit_e:
	add $t0, $t1, $zero
	beq $t1, $zero, DFS_global_shortcircuit_f
	add $t2, $zero, $zero
	addi $t4, $sp, 8
	lw $t4, 0($t4)
	addi $t5, $a0, 0
	lw $t5, 0($t5)
	sub $t6, $t4, $t5
	li $t4, 15
	add $t5, $t6, $t4
	li $t3, 100
	mul $t2, $t2, $t3
	add $t2, $t2, $t5
	li $t3, 4
	mul $t2, $t2, $t3
	la $t3, c_global
	add $t2, $t3, $t2
	lw $t2, 0($t2)
	seq $t2, $zero, $t2
	add $t0, $t2, $zero

DFS_global_shortcircuit_f:
	beq $t0, $zero, DFS_global_endif_d
	li $t0, 1
	add $t1, $zero, $zero
	addi $t3, $sp, 8
	lw $t3, 0($t3)
	li $t2, 100
	mul $t1, $t1, $t2
	add $t1, $t1, $t3
	li $t2, 4
	mul $t1, $t1, $t2
	la $t2, a_global
	add $t1, $t2, $t1
	sw $t0, 0($t1)
	li $t0, 1
	add $t1, $zero, $zero
	addi $t3, $sp, 8
	lw $t3, 0($t3)
	addi $t4, $a0, 0
	lw $t4, 0($t4)
	add $t5, $t3, $t4
	li $t2, 100
	mul $t1, $t1, $t2
	add $t1, $t1, $t5
	li $t2, 4
	mul $t1, $t1, $t2
	la $t2, v_global
	add $t1, $t2, $t1
	sw $t0, 0($t1)
	li $t0, 1
	add $t1, $zero, $zero
	addi $t3, $sp, 8
	lw $t3, 0($t3)
	addi $t4, $a0, 0
	lw $t4, 0($t4)
	sub $t5, $t3, $t4
	li $t3, 15
	add $t4, $t5, $t3
	li $t2, 100
	mul $t1, $t1, $t2
	add $t1, $t1, $t4
	li $t2, 4
	mul $t1, $t1, $t2
	la $t2, c_global
	add $t1, $t2, $t1
	sw $t0, 0($t1)
	addi $t0, $sp, 8
	lw $t0, 0($t0)
	add $t1, $zero, $zero
	addi $t3, $a0, 0
	lw $t3, 0($t3)
	li $t2, 100
	mul $t1, $t1, $t2
	add $t1, $t1, $t3
	li $t2, 4
	mul $t1, $t1, $t2
	la $t2, b_global
	add $t1, $t2, $t1
	sw $t0, 0($t1)
	addi $t0, $a0, 0
	lw $t0, 0($t0)
	li $t1, 1
	add $t2, $t0, $t1
	sw $t2, 20($sp)
	addi $a0, $sp, 20
	jal DFS_global
	add $t0, $v0, $zero
	lw $a0, 4($sp)
	li $t0, 0
	add $t1, $zero, $zero
	addi $t3, $sp, 8
	lw $t3, 0($t3)
	li $t2, 100
	mul $t1, $t1, $t2
	add $t1, $t1, $t3
	li $t2, 4
	mul $t1, $t1, $t2
	la $t2, a_global
	add $t1, $t2, $t1
	sw $t0, 0($t1)
	li $t0, 0
	add $t1, $zero, $zero
	addi $t3, $sp, 8
	lw $t3, 0($t3)
	addi $t4, $a0, 0
	lw $t4, 0($t4)
	add $t5, $t3, $t4
	li $t2, 100
	mul $t1, $t1, $t2
	add $t1, $t1, $t5
	li $t2, 4
	mul $t1, $t1, $t2
	la $t2, v_global
	add $t1, $t2, $t1
	sw $t0, 0($t1)
	li $t0, 0
	add $t1, $zero, $zero
	addi $t3, $sp, 8
	lw $t3, 0($t3)
	addi $t4, $a0, 0
	lw $t4, 0($t4)
	sub $t5, $t3, $t4
	li $t3, 15
	add $t4, $t5, $t3
	li $t2, 100
	mul $t1, $t1, $t2
	add $t1, $t1, $t4
	li $t2, 4
	mul $t1, $t1, $t2
	la $t2, c_global
	add $t1, $t2, $t1
	sw $t0, 0($t1)

DFS_global_endif_d:

DFS_global_for_incr_c:
	addi $t0, $sp, 8
	lw $t1, 0($t0)
	addi $t1, $t1, 1
	sw $t1, 0($t0)
	j DFS_global_for_cond_c

DFS_global_for_end_c:
	li $t0, 0
	add $v0, $t0, $zero
	j DFS_global_end

DFS_global_end:
	lw $ra, 0($sp)
	addi $sp, $sp, 24
	jr $ra

main:
	li $t0, 12
	sub $sp, $sp, $t0
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	la $t0, n_global
	add $a1, $v0, $zero
	li $v0, 5
	syscall
	sw $v0, 0($t0)
	add $v0, $a1, $zero
	li $t0, 1
	sw $t0, 8($sp)
	addi $a0, $sp, 8
	jal DFS_global
	add $t0, $v0, $zero
	lw $a0, 4($sp)
	la $t0, s_global
	lw $t0, 0($t0)
	add $a1, $v0, $zero
	add $a2, $a0, $zero
	li $v0, 1
	add $a0, $t0, $zero
	syscall
	add $v0, $a1, $zero
	add $a0, $a2, $zero
	li $t0, 0
	add $v0, $t0, $zero
	j main_end

main_end:
	lw $ra, 0($sp)
	addi $sp, $sp, 12
	jr $ra
