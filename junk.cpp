This will be your grammar file in future assignments
Leave it as it is for now
GRAMMAR:

---------------------ORIGINAL------------------------------

start -> comment start | func start | main

main -> kaam markazi functype () blks 
	  statements 
	  flke

func -> kaam id functype (params) blks
	  statements
	  fblke

functype -> @adad | @khali

statements -> comment statements | declare statements | input statements | output statements | loop statements | if statements | 
		  return statements | null

params -> id vartype sep

sep -> |params | null (first '|' stands for pipe sign to separate parameters, second '|' stands for or for cfg productions)

comment -> ; cmt

declare -> rakho id vartype ; | rakho id vartype := val ; | rakho id := val ;

val -> num | chalao id (args) | exp

args -> id args_ | num args_

args_ -> |args | null (first '|' stands for pipe sign to separate arguments, second '|' stands for or for cfg productions)

vartype -> @adad

input -> lo >> id ; | lo << str >> id ;

output -> dekhao output_ ;

output_ -> << out_ output_ | << out_

out_ -> id | str | chr

loop -> jab tak (exp) blks
	  statements
	  blke

exp -> exp + exp_ rel | exp - exp_ rel | exp_

exp_ -> exp_ % expval rel | exp_ * expval rel | exp_ / expval rel | expval rel

expval -> id | num | (exp)

rel -> <= exp | < exp | >= exp | > exp | <> exp | = exp | null

_if -> agar (exp) to phir blks
	 statements
	 _elseif
	 _else
	 blke

_elseif -> warna agar (exp) to phir
	     statements
	     _else | null

_else -> warna phir 
	   statements | null

blks -> karo

blke -> bas karo

fblke -> kaam khatam

ret -> wapas bhaijo num ; | wapas bhaijo

------------------------LL1--------------------------------

start -> comment start | func start | main

main -> kaam markazi functype () blks 
	  statements 
	  flke

func -> kaam id functype (params) blks
	  statements
	  fblke

functype -> @adad | @khali

statements -> comment statements | declare statements | input statements | output statements | loop statements | if statements | 
		  return statements | null

params -> id vartype sep

sep -> |params | null (first '|' stands for pipe sign to separate parameters, second '|' stands for or for cfg productions)

comment -> ; cmt

declare -> rakho id {declare_.n = id.lex} declare_

declare_ -> vartype {declare__.n = declare_.n} declare__

declare_ -> := val ; {print(declare_.n, "=", val.v) nl++;}

declare__ -> ;

declare__ -> := val ; {print(declare__.n, "=", val.v) nl++;}

val -> num {val.v = num.lexeme}
val -> chalao id (args) {var = newtmp(); print("call", id.lex, args.s, "," var); val.v=var}
val -> exp {val.v = exp.lexeme}

args -> id {print("param", id.lex); nl++;} args_ {args.s = args_.s + 1}

args -> num {print("param", num.lex); nl++;} args_ {args.s = args_.s + 1}

args_ -> |args {args_.s = args.s} (first '|' stands for pipe sign to separate arguments, second '|' stands for or for cfg productions) 

args_ -> null {args_.s = 0}

vartype -> @adad

input -> lo input_

input_ -> >> {print("in", id.lex) nl++;} id ;

input_ -> << str {print("out", str.lex) nl++;} >> id ; {print("in", id.lex) nl++;}

output -> dekhao output_ ;

output_ -> << out_ {print("out", out_.n) nl++;} output__

output__ -> output_ | null

out_ -> id {out_.n = id.lex}
out_ -> str {out_.n = id.lex}
out_ -> chr {out_.n = id.lex} 

loop -> jab tak (exp) {print("if", exp.n. "goto", "loopt"); nl++;
		       print("goto", "loopf"); nl++;}
			{fillblank(loopt, nl)}
	  blks
	  statements {print("goto", loopt); nl++;}
			 {fillblank(loopf, nl);}
	  blke

exp -> exp_ R {exp.v = exp_.v + R.v}

exp_ -> expval rel P {exp_.v = expval.v + rel.v + P.v}

R -> + exp_ rel R1 {R.v = "+" + exp_.v + rel.v + R1.v}
R -> - exp_ rel R1 {R.v = "-" + exp_.v + rel.v + R1.v}
R -> null {R.v = ""}

P -> % expval rel P1 {P.v = "%"+expval.v+rel.v+P1.v}
P -> * expval rel P1 {P.v = "*"+expval.v+rel.v+P1.v}
P -> / expval rel P1 {P.v = "/"+expval.v+rel.v+P1.v}
P -> null {P.v = ""}

expval -> id {expval.v = id.lexeme} 
expval -> num {expval.v = num.lexeme}
expval -> (exp) {expval.v = "("+exp.v+")"}

rel -> <= exp {rel.v="<="+exp.v}
rel -> < exp {rel.v="<"+exp.v}
rel -> >= exp {rel.v=">="+exp.v}
rel -> > exp {rel.v=">"+exp.v}
rel -> <> exp {rel.v="<>"+exp.v}
rel -> = exp {rel.v="="+exp.v}
rel -> null {rel.v=""}

_if -> agar (exp) {print("if", exp.n. "goto", "t1"); nl++;
		       print("goto", "f1"); nl++;}
			{fillblank(t1, nl)} 
	 to phir blks
	 statements {print("goto", "nn1"); nl++;}
	 		{fillblank(f1, nl);} 
	 _elseif 
	 _else {fillblank(nn1, nl);}
	 blke

_elseif -> warna agar (exp) {print("if", exp.n. "goto", "t2"); nl++;
		   		     print("goto", "f2"); nl++;}
				    {fillblank(t2, nl)} 
	     to phir
	     statements {print("goto", "nn2"); nl++;}
	     		    {fillblank(f2, nl);} 
	     _else {fillblank(nn2, n);}

_elseif -> null

_else -> warna phir 
	   statements 

_else -> null

blks -> karo

blke -> bas karo

fblke -> kaam khatam

ret -> wapas bhaijo ret_

ret_ -> num ; {print("ret", toString(num.lex)); n1++;}

ret_ -> null {print("ret") n1++;}


Regular Expressions used in GRAMMAR

id -> (letter)(letter|digit)*
num -> (digit)*
str -> `(digit+letter)*`
chr -> `(digit+letter)`
cmt -> ;( ` + ro + io + letter + digit)
ro -> <=|<|>=|>|=|<>
io -> >>|<<
letter -> _|A|B|...|Z|a|b|...|z
digit -> 0|1|...|9
