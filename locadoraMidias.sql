password: aluno
\l
\c 'nome do BD'
\i 'caminho do arquivo'



==========CONSULTAS============



CONSULTA 1


1.	SELECT * FROM mídias;
	
3.	SELECT * FROM mídias;

4.	SELECT título FROM filmes;

5.	SELECT nome FROM atores ORDER BY nome;

6.	SELECT título FROM filmes ORDER BY título DESC;

7.	SELECT nome FROM atores WHERE nome = 'John';

8.	SELECT título FROM filmes WHERE ator = 'John Ford';

9.	SELECT título FROM filmes WHERE categoria = 1;

10.	SELECT título FROM filmes WHERE categoria NOT IN (1, 2);

11.	SELECT nome FROM atores WHERE data_nasc IS NULL;

12.	SELECT título FROM filmes WHERE título LIKE '%amanhecer%';

13.	SELECT título FROM filmes WHERE título LIKE 'O%';

14.	SELECT título FROM filmes WHERE título LIKE '_o%';

15.	SELECT nome FROM atores WHERE data_nasc BETWEEN '1970-02-01' AND '1970-02-05' ORDER BY data_nasc;

16.	SELECT nome FROM atores WHERE nome LIKE '%nh%';



CONSULTA 2


1.	SELECT CURRENT_DATE;

2.	SELECT id_filme, valor, valor * 1.10 AS valor_com_aumento FROM locacao;   

3.	SELECT id_filme, valor, valor * 1.10 AS valor_com_aumento, (valor * 1.10 - valor) AS diferenca FROM locacao;

4.	SELECT UPPER(nome) FROM atores;

5.	SELECT LOWER(nome) FROM atores;

6.	SELECT nome || ' - ' || data_nasc FROM atores;

7.	SELECT * FROM filmes WHERE título LIKE '%A%';

8.	SELECT LEFT(título, 1) AS primeira_letra_título, categoria FROM filmes;

9.	SELECT * FROM locacao WHERE data >= (CURRENT_DATE - INTERVAL '10 days');

10.	SELECT * FROM locacao WHERE data BETWEEN (CURRENT_DATE - INTERVAL '20 days') AND (CURRENT_DATE - INTERVAL '15 days');

11.	SELECT nome FROM atores WHERE EXTRACT(MONTH FROM data_nasc) = EXTRACT(MONTH FROM CURRENT_DATE) AND EXTRACT(DAY FROM data_nasc) BETWEEN EXTRACT(DAY FROM CURRENT_DATE) AND (EXTRACT(DAY FROM CURRENT_DATE) + 7);



CONSULTA 3


1.	SELECT f.id_filme, f.título, a.nome
	FROM filmes f
	JOIN participacao p ON f.id_filme = p.id_filme
	JOIN atores a ON p.id_ator = a.id_ator;

2.	SELECT f.id_filme, a.nome, a.data_nasc
	FROM filmes f
	JOIN participacao p ON f.id_filme = p.id_filme
	JOIN atores a ON p.id_ator = a.id_ator;

3.	SELECT l.id_filme, l.id_cliente, c.nome
	FROM locacao l
	JOIN clientes c ON l.id_cliente = c.id_cliente
	WHERE l.id_cliente = 5;

4.	SELECT f.título
	FROM filmes f
	JOIN mídias m ON f.id_filme = m.id_filme;

5.	SELECT c.nome
	FROM clientes c
	JOIN locacao l ON c.id_cliente = l.id_cliente
	JOIN filmes f ON l.id_filme = f.id_filme
	WHERE f.título = 'O vento levou';

6.	SELECT f.título
	FROM filmes f
	LEFT OUTER JOIN locacao l ON f.id_filme = l.id_filme
	WHERE l.id_filme IS NULL;
	
	

CONSULTA 4


1.	SELECT MAX(valor) AS maior_valor, MIN(valor) AS menor_valor, AVG(valor) AS valor_médio
	FROM locacao;

2.	SELECT MAX(data_nasc) AS ator_mais_velho, MIN(data_nasc) AS ator_mais_novo
	FROM atores;

3.	SELECT STDDEV(valor) AS desvio_padrao, VARIANCE(valor) AS variancia
	FROM locacao;

4.	SELECT DECIMAL(MAX(valor), 10, 2) AS maior_valor, DECIMAL(MIN(valor), 10, 2) AS menor_valor, DECIMAL(AVG(valor), 10, 2) AS valor_médio
				FROM locacao;

	SELECT DECIMAL(MAX(data_nasc), 10, 2) AS ator_mais_velho, DECIMAL(MIN(data_nasc), 10, 2) AS ator_mais_novo
	FROM atores;

	SELECT DECIMAL(STDDEV(valor), 10, 2) AS desvio_padrao, DECIMAL(VARIANCE(valor), 10, 2) AS variancia
	FROM locacao;

5.	SELECT id_cliente, SUM(valor) AS valor_total_pago
	FROM locacao
	GROUP BY id_cliente;

6.	SELECT id_cliente, SUM(valor) AS valor_total_pago
	FROM locacao
	GROUP BY id_cliente
	ORDER BY valor_total_pago DESC;

7.	SELECT a.nome AS nome_ator, COUNT(p.id_filme) AS numero_participacoes
	FROM atores a
	LEFT OUTER JOIN participacao p ON a.id_ator = p.id_ator
	GROUP BY a.id_ator, a.nome;

8.	SELECT MAX(valor) - MIN(valor) AS diferenca
	FROM locacao;
	
9.	SELECT id_cliente, MIN(valor) AS menor_valor_locacao
	FROM locacao
	GROUP BY id_cliente;



CONSULTA 5


1.	SELECT * FROM imoveis WHERE bairro = (SELECT bairro FROM imoveis WHERE codigo_imovel = 2) AND codigo_imovel != 2;

2.	SELECT * FROM imoveis WHERE preco > (SELECT AVG(preco) FROM imoveis);

3.	SELECT comprador FROM ofertas WHERE valor_oferta > 70000;

4.	SELECT * FROM imoveis WHERE oferta > (SELECT AVG(oferta) FROM imoveis);

5.	SELECT * FROM imoveis WHERE preco > (SELECT AVG(preco) FROM imoveis WHERE bairro = (SELECT bairro FROM imoveis WHERE codigo_imovel = <código_imovel>));

6.	SELECT bairro, MAX(preco) AS maior_preco FROM imoveis GROUP BY bairro HAVING MAX(preco) > (SELECT AVG(preco) FROM imoveis);

7.	SELECT * FROM imoveis WHERE (codigo_vendedor, preco) IN (SELECT codigo_vendedor, MIN(preco) FROM imoveis GROUP BY codigo_vendedor);

8.	SELECT * FROM ofertas WHERE codigo_vendedor = 2 AND data_lancamento BETWEEN NOW() - INTERVAL '180 days' AND NOW() - INTERVAL '30 days';

9.	SELECT * FROM imoveis WHERE preco = (SELECT MIN(preco) FROM imoveis WHERE codigo_vendedor <> <código_vendedor>);

10.	SELECT * FROM ofertas WHERE valor_oferta < ALL (SELECT valor_oferta FROM ofertas WHERE comprador = 2 AND codigo_oferta <> <código_oferta>);

11.	SELECT * FROM imoveis WHERE estado = (SELECT estado FROM imoveis WHERE codigo_imovel = 5) AND cidade = (SELECT cidade FROM imoveis WHERE codigo_imovel = 5) AND bairro = (SELECT bairro FROM imoveis WHERE codigo_imovel = 5) AND codigo_vendedor != 3;

12.	SELECT DISTINCT bairro FROM imoveis WHERE estado = (SELECT estado FROM imoveis WHERE codigo_imovel = 5) AND cidade = (SELECT cidade FROM imoveis WHERE codigo_imovel = 5) AND bairro = (SELECT bairro FROM imoveis WHERE codigo_imovel = 5);

