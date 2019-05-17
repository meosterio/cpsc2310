comment(` Alex Moore')
comment(` CPSC 2311 - Sec 3')
comment(` Lab 1')

comment(` code that implements the loop with ble0 at top of loop ')

comment(`  code that implements the loop                       ')
comment(`    sum = 0;                                          ')
comment(`    for( i = 1; i <= 10; i++ ) {                      ')
comment(`       sum = sum + i;                                 ')
comment(`    }                                                 ')

  word(sum,0)
  word(i,0)
  word(zero,0)
  word(one,1)
  word(j,0)
  word(ten,10)

label(start)

  load(zero)
  store(sum)
  load(one)
  store(i)
  load(ten)
  store(j)

label(loop)

  load(j)       comment(' branch to done if j < 0        ')
  ble0(done)

  load(sum)     comment(' sum = sum + i                   ')
  add(i)
  store(sum)

  load(i)       comment(' i = i + 1                       ')
  add(one)
  store(i)

  load(j)       comment(' j = j - 1                       ')
  sub(one)
  store(j)

  ba(loop)      comment(' unconditionally go back to loop ')

label(done)

  print(sum)
  halt

comment(' start execution at label start  ')

  end(start)
