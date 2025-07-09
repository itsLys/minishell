# parsing:

/bin/echo $"42$"
/bin/echo $USER'$USER'text oui oui     oui  oui $USER oui      $USER ''
/bin/echo '' ""
/bin/echo $USER$TESTNOTFOUND$HOME$
echo '' -n
echo "" "" "" -n -n -n -n
$NOVAR
echo '$'$'$'$'$'
echo "$"$'$'$"$"$"$"$'$'
<| echo ok #syntax error stderr
exit ""

# execution

