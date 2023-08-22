# Notities
## var struct
Voorlopige indeling van de variabelenopslag-struct (env en lokale):
+ Array + (size\_t n\_var, size\_t n\_occupied)
	+ Toevoegen (`=`; `export`): zoeken naar lege plekken, anders heralloceren;
	+ Verwijderen (`unset`): entries daaronder naar boven verplaatsen
	+ Variabele: `struct s_var {char \*name; char\* value};`
	N.B. execve() vereist envp als char ** waarbij iedere variabele de vorm `<naam>=<waarde>` heeft. Conversiefunctie?

## executor
Voor forken env consolideren
Vier opties:
1. geen pad, naam is builtin: Voer builtin uit.
2. geen pad, naam is geen builtin: Zoek $PATH af naar naam; voer uit indien gevonden.
3. pad: Zoek pad af naar naam; voer uit indien gevonden.
4. eerste woord bevat '=' en geen aanhalingstekens: bewerk loc\_vars. Sla over indien nog meer volgt.

in main checken of argc meer dan 1 is en in dat geval checken or -c als argument gegeven is en als dat zo is het gegeven commando uitvoeren

namen van de in, out en error files doorgeven uit de parser aan de commands, dit maakt het makkelijker om met pipes te werken
- dan kan ieder commando een link uit de linked list krijgen

builtins in pipes moeten wel in een child
 - niet met execve

cd | pwd verandert niet de directory

array van command structs doorgeven aan de executor

shlvl verhoogt als je msh in msh opent

## msh\_lex

`t_errno	lex(t_list **tokens, char const *line)`
Splits `line` into tokens and appends them to `tokens`
Returns `MSH_SUCCESS` on success, `MSH_MEMFAIL` on memory failure and `MSH_INCOMPLETE_TOKEN` upon generating an incomplete token (i.e. a token with improperly closed quotes). This token should be completed with another invocation to `lex()` before passing `tokens` to `parse()`.

## msh\_parse

`t_errno	parse(t_list **tokens, t_list **cmds, t_msh *msh)`
Parses the tokens contained in `tokens` into commands, which are appended to `cmds`. Note that tokens are **consumed** during parsing; upon completion, `tokens` will be empty.
Returns `MSH_SUCCESS` on success, `MSH_MEMFAIL` on memory failure and `MSH_SYNTAX_ERROR` upon encountering an improper token sequence (e.g. two successive `>` `>>` tokens).

## msh\_expand

`t_errno	expand(t_list **words, t_msh *msh)`
Expands variable names within the string contained in the first node of `words` (any following nodes are discarded), processes quotes and performs field splitting. The result is pushed (not appended!) onto `words`, yielding a list of words.
Returns `MSH_SUCCESS` on success or `MSH_MEMFAIL` on memory failure.
_Internally, during expansion, the string is paired with a parallel array of expander operations which determine what should be done with each character in the string during field splitting. This character can be copied to output (this is true in most cases), signify the end of a word (i.e. unquoted whitespace) or be ignored (e.g. opening and closing quotes).__
Future extensions may include wildcard expansion and escape sequence support (through another expander operation: 'ignore this character but do something special with the following character').

## Notes

### Syntax
- variabelen invullen
	- kan alleen vooraan:
```
VARa=a VARb=b		<-- VARa en VARb krijgen beide een waarde
cat in VAR=a		<-- VAR=a is een parameter van cat
```
	- als dezelfde opdracht een programma bevat: alleen in subshell
```
VAR=a cat in		<-- cat wordt uitgevoerd, VAR is leeg
```

### Expander
- eerst $-uitklapping
- dan *-uitklapping:
	- haal mogelijke aanvullingen op met  (. = alles wat vóór * staat, of msh->env->pwd indien er niets staat)
	- genereer lijst op basis van alle mogelijke aanvullingen * -> [a b c]
	- lijst kan zich recursief vertakken (*/* -> [a b c]/* -> [a/* b/* c/*] -> [[a/d a/e] [b/f b/g] [c/h c/i]]
	- vlak lijst af [[a/d a/e] [b/f b/g] [c/h c/i]] -> a/d a/e b/f b/g c/h c/i
	- laat * staan indien aanvullingen ontbreken
- geen woordsplitsing (of *-uitklapping) bij schrijven naar variabele

cd && pwd in een subshell verandert wel de directory

### Environment
- net als in bash moeten we een environment hebben die nooit helemaal leeg raakt, de _ blijft altijd staan
