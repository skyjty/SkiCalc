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

### SkiCalc使用
1. 运行GenerateProject.bat，使用premake生成vs文件（在中文路径下会报错）；
2. 使用vs打开项目项目文件SkiCalc.sln，编译运行；
3. 如果需要使用计算器程序而非运行测试，在项目-配置启动项目中选择SkiCalcApp，即可运行计算器程序。