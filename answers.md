# Exercise 1
* `w01-byte` bytes/second: 4236 
* `w02-byte` bytes/second: 929203 
* `w03-byte` bytes/second: 2,97994*10⁷ 

# Exercise 2
### Scenario 1:
* How many array elements can fit into a cache block?
 	2 elementos pois cada elemento é um inteirro de 4 bytes e cada bloco tem tamanhode 8 bytes
* What combination of parameters is producing the hit rate you observe? Think about the sizes of each of the parameters.
	Nesse cenário o stepSize = 1 e repCount = 2 resultaram em um hit rate = 0,5 porque cada bloco da cache pode armazenar apenas 2 elementos do vetor e a cache possui somente um bloco neste caso, na primeira varredura pelo vetor, o algoritmo tenta acessar a primeira posição do vetor, mas, como o elemento ainda não está na cache, ocorre um miss, e o bloco correspondente é carregado na cache contendo o primeiro e segundo elemento do vetor, devido à política de write-allocate. Assim, o primeiro acesso ao bloco gera um miss, o segundo acesso gera um hit. Esse padrão de 1 miss seguido de 1 hit resulta no hit rate de 0,5. No entanto, como há espaço suficiente na cache para armazenar apenas 1 bloco de cada vez (2 elementos do vetor), após cada hit (duas escritas no bloco), o próximo acesso resulta em um miss, pois o bloco anterior não possui o elemento buscado.
	Na segunda varredura (com repCount = 2), o bloco da cache contem o penultimo e ultimo elemento do vetor, mas a varedura começa pelo inicio do vetor. Por isso, a cache precisa recarregar os elementos buscados na cache, mantendo o mesmo padrão de alternância entre misses e hits que ocorreu na primeira varredura pelo vetor e preservando o hit rate = 0,5 mesmo com a repetição.

* What is our hit rate if we increase Rep Count arbitrarily? Why?
	O hit rate permanecerá em 0,5, pois a cache possui apenas 1 bloco, capaz de armazenar apenas dois elementos do vetor. Para qualquer vetor com tamanho maior que 2, cada varredura pelo vetor (Rep Count) resultará em um padrão fixo: uma iteração que causa um miss, seguida por uma iteração que causa um hit (o elemento seguinte foi carregado na memória após o miss). Esse comportamento se mantem independentemente do número de repetições, resultando consistentemente em um hit rate de 0,5.

### Scenario 2:
* What combination of parameters is producing the hit rate you observe? Think about the sizes of each of the parameters.
	A cache possui apenas 1 bloco, capaz de armazenar apenas 2 elementos do vetor. Com um stepSize = 27 e um tamanho de vetor de 32 elementos, na primeira varredura pelo vetor, cada iteração resulta em um miss, já que o passo é maior do que a quantidade de elementos que a cache pode conter, ao acessar o primeiro elemento do vetor ocorre um miss e são carregados o primeiro e segundo elemento no bloco da cache devido a politica de write-alloc, o próximo acesso gera outro miss onde são carregados o vigésimo sétimo e vigésimo oitavo elementos do vetor e assim acaba a primeira varredura.
	No inicio da segunda varredura pelo vetor os dados que estão no bloco da cache são o vigésimo sétimo e vigésimo oitavo elementos do vetor, então os dados buscados terão que ser novamente carregados na cache. Isso recria a mesma situação da primeira varredura, onde todos os acessos também geram misses. Portanto, o hit rate é 0, já que não há acessos atendidos pela cache.

* What happens to our hit rate if we increase the number of blocks and why?
	Para qualquer cache com mais de 1 bloco, haverá 2 misses e 2 hits. As faltas ocorrem durante a primeira varredura pelo vetor, pois, na primeira iteração, o início do vetor é acessado e, como a cache está vazia, ocorre um miss. O primeiro e segundo elemento é então carregado na cache devido à política de write-allocate. Em seguida, o algoritmo salta 27 elementos e acessa o vetor novamente, gerando outro miss, com o vigésimo sétimo e vigésimo oitavo elementos sendo armazenado em outro bloco da cache. Após isso, a primeira varredura termina.
	Na segunda varredura pelo vetor, como os blocos da cache já contêm os valores necessários, cada acesso resulta em um hit. Como o vetor possui 32 elementos, a segunda varredura é atendida inteiramente pela cache. Dessa forma, o hit rate é de 0,5, já que metade dos acessos (2 de 4) foram hits.
### Scenario 3:
* Choose a `number of blocks` greater than `1` and determine the smallest `block size` that uses every block *and* maximizes the hit rate given the parameters above. Explain why.
Number of blocks: 4
Block Size: 32
	Cada bloco pode armazenar 8 elementos do vetor pois cada elemento é um inteirro de 4 bytes e cada bloco tem tamanhode 32 bytes (32 / 4 = 8 elementos), de forma que os 4 blocos da cache conseguem conter todos os 64 elementos do vetor neste cenário. Na primeira varredura pelo vetor, o acesso ao primeiro elemento gera um miss, e, pela política de write-allocate, os 8 primeiros elementos do vetor são carregados na cache. Em seguida, devido ao option = 1, ocorre também uma leitura do primeiro elemento, gerando um hit.
	O algoritmo então prossegue, avançando com um stepSize = 2, e cada iteração resulta em 2 hits, até que um elemento fora do bloco atual seja acessado (nono elemento do vetor), gerando um novo miss. Isso leva outro bloco da cache a carregar mais 8 elementos do vetor. Esse processo se repete até que todos os 64 elementos sejam carregados na cache ao final da primeira varredura.
	Na segunda varredura, como todos os elementos necessários já estão na cache, cada iteração gera 2 acessos, em que cada acesso gera hit, até que o algoritmo termine.
	Dessa forma, o hit rate neste cenário em que há duas repetições (varreduras pelo vetor) é de 0,875, o maior possível para o menor tamanho de bloco (8 elementos) em uma cache de 4 blocos, onde todos os blocos são utilizados.
# Exercise 3
* Order the functions from fastest to slowest, and explain why each function's ranking makes sense using your understanding of how the cache works. Some functions might have similar runtimes. If this is the case, explain why.
<!-- Fill this in -->
