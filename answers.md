# Exercise 1
* `w01-byte` bytes/second: 4236 
* `w02-byte` bytes/second: 929203 
* `w03-byte` bytes/second: 2,97994*10⁷ 

# Exercise 2
### Scenario 1:
* How many array elements can fit into a cache block?
 	2 elementos pois cada elemento é um inteiro de 4 bytes e cada bloco tem tamanho de 8 bytes
* What combination of parameters is producing the hit rate you observe? Think about the sizes of each of the parameters.
	Nesse cenário o stepSize = 1 e repCount = 2 resultaram em um hit rate = 0,5 porque cada bloco da cache pode armazenar apenas 2 
	elementos do vetor e a cache possui somente um bloco neste caso, na primeira varredura pelo vetor, o algoritmo tenta acessar a 
	primeira posição do vetor, mas, como o elemento ainda não está na cache, ocorre um miss, e o bloco correspondente é carregado 
	na cache contendo o primeiro e segundo elemento do vetor, devido à política de write-allocate. Assim, o primeiro acesso 
	ao bloco gera um miss, o segundo acesso gera um hit. Esse padrão de 1 miss seguido de 1 hit resulta no hit rate de 0,5. 
	No entanto, como há espaço suficiente na cache para armazenar apenas 1 bloco de cada vez (2 elementos do vetor), após 
	cada hit (duas escritas no bloco), o próximo acesso resulta em um miss, pois o bloco anterior não possui o elemento buscado.
	Na segunda varredura (com repCount = 2), o bloco da cache contem o penultimo e ultimo elemento do vetor, mas a varedura 
	começa pelo inicio do vetor. Por isso, a cache precisa recarregar os elementos buscados na cache, mantendo o mesmo padrão 
	de alternância entre misses e hits que ocorreu na primeira varredura pelo vetor e preservando o hit rate = 0,5 mesmo com a repetição.

* What is our hit rate if we increase Rep Count arbitrarily? Why?
	O hit rate permanecerá em 0,5, pois a cache possui apenas 1 bloco, capaz de armazenar apenas dois elementos do vetor. 
	Para qualquer vetor com tamanho maior que 2, cada varredura pelo vetor (Rep Count) resultará em um padrão fixo: uma iteração 
	que causa um miss, seguida por uma iteração que causa um hit (o elemento seguinte foi carregado na memória após o miss). 
	Esse comportamento se mantem independentemente do número de repetições, resultando consistentemente em um hit rate de 0,5.

### Scenario 2:
* What combination of parameters is producing the hit rate you observe? Think about the sizes of each of the parameters.
	A cache possui apenas 1 bloco, capaz de armazenar apenas 2 elementos do vetor. Com um stepSize = 27 e um tamanho de vetor de 32 elementos, 
	na primeira varredura pelo vetor, cada iteração resulta em um miss, já que o passo é maior do que a quantidade de elementos que a cache pode 
	conter, ao acessar o primeiro elemento do vetor ocorre um miss e são carregados o primeiro e segundo elemento no bloco da cache devido a politica 
	de write-alloc, o próximo acesso gera outro miss onde são carregados o vigésimo sétimo e vigésimo oitavo elementos do vetor e assim acaba a 
	primeira varredura. No inicio da segunda varredura pelo vetor os dados que estão no bloco da cache são o vigésimo sétimo e vigésimo oitavo elementos 
	do vetor, então os dados buscados terão que ser novamente carregados na cache. Isso recria a mesma situação da primeira varredura, onde todos os 
	acessos também geram misses. Portanto, o hit rate é 0, já que não há acessos atendidos pela cache.

* What happens to our hit rate if we increase the number of blocks and why?
	Para qualquer cache com mais de 1 bloco, haverá 2 misses e 2 hits. As faltas ocorrem durante a primeira varredura pelo vetor, pois, na primeira iteração, 
	o início do vetor é acessado e, como a cache está vazia, ocorre um miss. O primeiro e segundo elemento é então carregado na cache devido à política de 
	write-allocate. Em seguida, o algoritmo salta 27 elementos e acessa o vetor novamente, gerando outro miss, com o vigésimo sétimo e vigésimo oitavo elementos 
	sendo armazenado em outro bloco da cache. Após isso, a primeira varredura termina.
	Na segunda varredura pelo vetor, como os blocos da cache já contêm os valores necessários, cada acesso resulta em um hit. Como o vetor possui 32 elementos, 
	a segunda varredura é atendida inteiramente pela cache. Dessa forma, o hit rate é de 0,5, já que metade dos acessos (2 de 4) foram hits.
### Scenario 3:
* Choose a `number of blocks` greater than `1` and determine the smallest `block size` that uses every block *and* maximizes the hit rate given the parameters above. Explain why.
Number of blocks: 4
Block Size: 32
	Cada bloco pode armazenar 8 elementos do vetor pois cada elemento é um inteirro de 4 bytes e cada bloco tem tamanhode 32 bytes (32 / 4 = 8 elementos), 
	de forma que os 4 blocos da cache conseguem conter todos os 64 elementos do vetor neste cenário. Na primeira varredura pelo vetor, o acesso ao primeiro 
	elemento gera um miss, e, pela política de write-allocate, os 8 primeiros elementos do vetor são carregados na cache. Em seguida, devido ao option = 1, 
	ocorre também uma leitura do primeiro elemento, gerando um hit.
	O algoritmo então prossegue, avançando com um stepSize = 2, e cada iteração resulta em 2 hits, até que um elemento fora do bloco atual seja acessado 
	(nono elemento do vetor), gerando um novo miss. Isso leva outro bloco da cache a carregar mais 8 elementos do vetor. Esse processo se repete até que 
	todos os 64 elementos sejam carregados na cache ao final da primeira varredura.
	Na segunda varredura, como todos os elementos necessários já estão na cache, cada iteração gera 2 acessos, em que cada acesso gera hit, até que o algoritmo termine.
	Dessa forma, o hit rate neste cenário em que há duas repetições (varreduras pelo vetor) é de 0,875, o maior possível para o menor tamanho de bloco (8 elementos) 
	em uma cache de 4 blocos, onde todos os blocos são utilizados.
# Exercise 3
* Order the functions from fastest to slowest, and explain why each function's ranking makes sense using your understanding of how the cache works. Some functions might have similar runtimes. If this is the case, explain why.

# Desempenho das Funções de Multiplicação de Matrizes

As funções foram ordenadas com base no desempenho (GFLOP/s) obtido na execução com \(n = 1000\):

1. **jki**: 0.611 GFLOP/s
2. **kji**: 0.595 GFLOP/s
3. **ijk**: 0.513 GFLOP/s
4. **jik**: 0.453 GFLOP/s
5. **kij**: 0.200 GFLOP/s
6. **ikj**: 0.197 GFLOP/s

## Explicação do Desempenho

O desempenho de cada função depende diretamente de como os elementos das matrizes \(A\), \(B\) e \(C\) são acessados na memória. Isso é determinado pela localidade espacial e temporal no uso do cache.

### Motivo do Alto Desempenho das Funções Rápidas (**jki** e **kji**)

- **jki**: O loop externo \(j\) garante que os elementos da matriz \(B[k+j*n]\) sejam acessados de maneira sequencial (bom uso da localidade espacial). O loop intermediário \(k\) mantém \(A[i+k*n]\) fixo por mais tempo, aproveitando o cache.
- **kji**: O loop externo \(k\) varia enquanto \(j\) mantém \(B[k+j*n]\) acessado sequencialmente. Apesar de ser eficiente, o acesso a \(A[i+k*n]\) é menos otimizado em comparação com **jki**.

### Desempenho Médio (**ijk** e **jik**)

- **ijk**: \(B[k+j*n]\) é acessado de maneira razoável, mas não tão eficiente quanto as funções mais rápidas.
- **jik**: O loop externo \(j\) favorece \(B[k+j*n]\), mas os acessos à matriz \(A[i+k*n]\) são menos eficientes.

### Motivo do Baixo Desempenho (**kij** e **ikj**)

- **kij**: O loop externo \(k\) varia com muita frequência, quebrando a continuidade do acesso à matriz \(B[k+j*n]\).
- **ikj**: O loop intermediário \(k\) e o loop interno \(j\) causam acessos não sequenciais em \(B[k+j*n]\), resultando em muitos **cache misses**.

## Impacto do Cache no Desempenho

As funções mais rápidas aproveitam a hierarquia de memória de maneira eficiente, acessando os dados sequencialmente e reduzindo o número de acessos à memória principal. Abaixo, uma tabela resumo com os motivos do desempenho:

| **Ordem**  | **Motivo do Desempenho** |
|------------|--------------------------|
| **jki**    | Melhor localidade espacial em \(B[k+j*n]\) e \(A[i+k*n]\). |
| **kji**    | Boa localidade espacial em \(B[k+j*n]\), mas menos eficiente em \(A[i+k*n]\). |
| **ijk**    | Localidade razoável, mas com limitações para acesso a \(B[k+j*n]\). |
| **jik**    | Localidade razoável para \(B[k+j*n]\), mas com menos eficiência em \(A[i+k*n]\). |
| **kij**    | Quebra de localidade em \(B[k+j*n]\), resultando em muitos **cache misses**. |
| **ikj**    | Pouca localidade tanto em \(B[k+j*n]\) quanto em \(A[i+k*n]\). |

As diferenças no desempenho entre as funções são causadas principalmente pelo aproveitamento (ou não) da hierarquia de memória. Funções que exploram a localidade espacial de \(B[k+j*n]\) e \(A[i+k*n]\) têm desempenho superior. Já as funções com acessos aleatórios à memória sofrem penalidades devido aos altos custos de **cache misses**.

