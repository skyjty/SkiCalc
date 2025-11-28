### SkiCalc的BNF定义
```EBNF
<statement> ::= <expression> | <assignment>

<assignment> ::= <identifier> "=" <expression>

<expression> ::= <term> { ("+" | "-") <term> }

<term> ::= <factor> { ("*" | "/") <factor> }

<factor> ::= <number>
           | <identifier>
           | "-" <factor>
           | "(" <expression> ")"

<number> ::= <digit> { <digit> } [ "." { <digit> } ]

<identifier> ::= <letter> { <letter> | <digit> }

<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"

<letter> ::= "a" | "b" | ... | "z" | "A" | "B" | ... | "Z"
```

##