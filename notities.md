## msh\_lex

`t_errno	lex(t_list **tokens, char const *line)`
Splits `line` into tokens and appends them to `tokens`
Returns `MSH_SUCCESS` on success, `MSH_MEMFAIL` on memory failure and `MSH_INCOMPLETE_TOKEN` upon generating an incomplete token (i.e. a token with improperly closed quotes). This token should be completed with another invocation to `lex()` before passing `tokens` to `parse()`.

## msh\_parse

`t_errno	parse(t_list **tokens, t_list **cmds, t_msh *msh)`
Parses the tokens contained in `tokens` into commands, which are appended to `cmds`.
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
	- gebeurt niet als dezelfde opdracht een programma bevat
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
