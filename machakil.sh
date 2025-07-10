# parsing:

/bin/echo $"42$"
echo '$'$'$'$'$'
echo "$"$'$'$"$"$"$"$'$'
<| echo ok #syntax error stderr
exit ""

# execution

ls > out >> out1 >out3 | cat out1
ls > out >> out1 >out3 | cat out1
/bin/rm -f out
/bin/rm -f out1
/bin/rm -f out3

cat < Makefile > out >> out1 | wc -l out1 > out2
cat < Makefile > out >> out1 | wc -l out1 > out2
/bin/rm -f out
/bin/rm -f out1
/bin/rm -f out2

/bin/echo 42 > /dev/null > /dev/null > /dev/null > /dev/null > tmp_redir_out
cat tmp_redir_out
rm tmp_redir_out

/bin/echo 42 > tmp_redir_out > tmp_redir_out1 > tmp_redir_out2 > tmp_redir_out3
/bin/echo 0
cat tmp_redir_out
/bin/echo 1
cat tmp_redir_out1
/bin/echo 2
cat tmp_redir_out2
/bin/echo 3
cat tmp_redir_out3
rm tmp_redir_out tmp_redir_out1 tmp_redir_out2 tmp_redir_out3

/bin/echo 42 > /dev/null > tmp_redir_out
/bin/echo 2 >> /dev/null >> tmp_redir_out
cat tmp_redir_out
rm tmp_redir_out
