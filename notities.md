# Notities
## var struct
Voorlopige indeling van de variabelenopslag-struct (env en lokale):
+ Array + (size\_t n\_var, size\_t n\_occupied)
	+ Toevoegen (`=`; `export`): zoeken naar lege plekken, anders heralloceren;
	+ Verwijderen (`unset`): entries daaronder naar boven verplaatsen
	+ Variabele: `struct s_var {char \*name; char\* value};`
	N.B. execve() vereist envp als char ** waarbij iedere variabele de vorm `<naam>=<waarde>` heeft. Conversiefunctie?

## executor
Vier opties:
1. geen pad, naam is builtin: Voer builtin uit.
2. geen pad, naam is geen builtin: Zoek $PATH af naar naam; voer uit indien gevonden.
3. pad: Zoek pad af naar naam; voer uit indien gevonden.
4. eerste woord bevat '=' en geen aanhalingstekens: bewerk loc\_vars. Sla over indien nog meer volgt.

in main checken of argc meer dan 1 is en in dat geval checken or -c als argument gegeven is en als dat zo is het gegeven commando uitvoeren

fds doorgeven uit de parser aan de commands, dit maakt het makkelijker om met pipes te werken
- dan kan ieder commando een link uit de linked list krijgen