# Notities
## var struct
Voorlopige indeling van de variabelenopslag-struct (env en lokale):
+ Array + (size\_t n\_var, size\_t n\_occupied)
	+ Toevoegen (`=`; `export`): zoeken naar lege plekken, anders heralloceren;
	+ Verwijderen (`unset`): op NULL
	+ Variabele: `struct s_var {char \*name; char\* value};`
	N.B. execve() vereist envp als char ** waarbij iedere variabele de vorm `<naam>=<waarde>` heeft. Conversiefunctie?

## executor
Vier opties:
1. geen pad, naam is builtin: Voer builtin uit.
2. geen pad, naam is geen buildin: Zoek $PATH af naar naam; voer uit indien gevonden.
3. pad: Zoek pad af naar naam; voer uit indien gevonden.
4. eerste woord bevat '=' en geen aanhalingstekens: bewerk loc\_vars. Sla over indien nog meer volgt.
