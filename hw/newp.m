comment(`alex9             ')
comment(`CPSC 2310 Sec 001 ')
comment(`Program1          ')
comment(`1/30/18           ')

comment(` code that implements the loop with beq0 at top of loop     ')

comment(` Program finds the least common denominator of two integers ')
comment(`    if ( b == 0 ) return a;                                 ')
comment(`    r = 1;                                                  ')
comment(`    while ( r != 0 ) {                                      ')
comment(`       q = a/b;                                             ')
comment(`       r = a - (q)b;                                        ')
comment(`       a = b;                                               ')
comment(`       b = r;                                               ')
comment(`    }                                                       ')

  word(a,80)
  word(b,60)
  word(q, 0)
  word(r, 0)
  word(one, 1)
  word(hold, 0)

label(start)

  load(b)     comment(` branch to done if b == 0        ')
  beq0(done)

  load(one)   comment(` r = 1                           ')
  store(r)

label(loop)

  load(r)     comment(` branch to done if r == 0        ')
  beq0(done)

  load(a)     comment(` q = a / b                       ')
  div(b)
  store(q)

  load(q)     comment(` hold = q                        ')
  store(hold)

  load(hold)  comment(` hold = hold * b                 ')
  mul(b)
  store(hold)

  load(a)     comment(` r = a - hold                    ')
  sub(hold)
  store(r)

  load(b)     comment(` a = b                           ')
  store(a)

  load(r)     comment(` b = r                           ')
  store(b)

  ba(loop)    comment(` unconditionally go back to loop ')

label(done)

  print(a)
  halt

comment(' start execution at label start  ')

  end(start)
