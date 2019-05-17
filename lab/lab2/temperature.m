comment(` Alex Moore')
comment(` CPSC 2311 - Sec 3')
comment(` Lab 2')

comment(` working table from celcius to fahrenheit ')

bipush(-40)       comment(` load -40 for celcius                  ')
istore_1

bipush(-40)       comment(` load -40 for fahrenheit               ')
istore_2

iconst_1          comment(` print local register 1 ie. celcius    ')
invokevirtual(1)

iconst_2          comment(` print local register 2 ie. fahrenheit ')
invokevirtual(2)

label(loop)       comment(` begin the loop                        ')

iinc(1, 10)       comment(` increment local register 1 by 10      ')

iconst_1          comment(` print local register 1 ie. celcius    ')
invokevirtual(1)

iinc(2, 18)       comment(` increment local register 2 by 18      ')

iconst_2          comment(` print local register 2 ie. fahrenheit ')
invokevirtual(2)

iload_1           comment(` push the loop count onto the stack    ')
bipush(110)       comment(` push the loop limit onto the stack    ')

isub              comment(`pop top two numbers and subtract the 2nd from the 1st (loop count - 110)')

ifle(loop)

return
