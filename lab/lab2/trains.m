goto(main)

label(compute)
	comment(`Compute Intercept Time, using the formula below')

	comment(`  (Start_Time_B * Speed_A)')
	comment(`  ------------------------')
	comment(`    (Speed_B - Speed_A)   ')


	comment(` determine head start of Train A')
iload_2		comment(`Start Time Difference')
iload_0		comment(`Train A Speed')
imul

	comment(`Compute Speed Difference')
iload_1		comment(`Train B Speed')
iload_0		comment(`Train A Speed')
isub

idiv
istore_3	comment(`Time for Train B to catch Train A')

ret


label(main)

bipush(50)	comment(`initialize Train A to 50mph')
istore_0

bipush(65)	comment(`initialzie Train B to 65mph')
istore_1

bipush(60)	comment(`Train B leaves 1 hour after Train A')
istore_2

jsr(compute)

iconst_3
invokevirtual(2) comment(`call println to print intercept time')

return
