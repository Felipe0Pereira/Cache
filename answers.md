# Exercício 1
* `w01-byte` bytes/segundo: 4236 
* `w02-byte` bytes/segundo: 929203 
* `w03-byte` bytes/segundo: 2,97994*10⁷ 

# Exercício 2

## Cenário 1

### Perguntas:

**Quantos elementos de vetor cabem em um bloco da cache?**  
2 elementos, pois cada elemento é um inteiro de 4 bytes e cada bloco tem tamanho de 8 bytes.

**Que combinação de parâmetros está produzindo o hit rate que você observou? Pense sobre os valores de cada parâmetro.**  
Dados os parâmetros do cenário:  

**Parâmetros do Programa:**  
- Tamanho do Array: 128 bytes  
- Step Size: 1  
- Rep Count: 2  
- Opção: 0 (apenas escrita)  

**Parâmetros da Cache:**  
- Níveis de Cache: 1  
- Tamanho do Bloco: 8  
- Número de Blocos: 1  
- Política de Posicionamento: Mapeamento Direto  
- Política de Substituição de Bloco: LRU  

Nesse cenário, o **Step Size = 1** e **Rep Count = 2** resultaram em um **hit rate = 0,5**, porque cada bloco da cache pode armazenar apenas 2 elementos do vetor e a cache possui somente um bloco. Na primeira varredura pelo vetor, o algoritmo tenta acessar a primeira posição do vetor, mas, como o elemento ainda não está na cache, ocorre um **miss**, e o bloco correspondente é carregado na cache contendo o primeiro e segundo elementos do vetor, devido à política de **write-allocate**.  

O primeiro acesso ao bloco gera um miss, e o segundo acesso gera um hit. Esse padrão de 1 miss seguido de 1 hit resulta no **hit rate de 0,5**. No entanto, como há espaço suficiente na cache para armazenar apenas 1 bloco de cada vez (2 elementos do vetor), após cada hit, o próximo acesso resulta em um miss, pois o bloco anterior não possui o elemento buscado.  

Na segunda varredura (com **Rep Count = 2**), o bloco da cache contém o penúltimo e último elementos do vetor, mas a varredura começa pelo início do vetor. Por isso, a cache precisa recarregar os elementos buscados, mantendo o mesmo padrão de alternância entre **misses** e **hits** que ocorreu na primeira varredura, preservando o **hit rate = 0,5** mesmo com a repetição.  

**Qual é o hit rate se aumentarmos o Rep Count arbitrariamente? Por quê?**  
Com os mesmos parâmetros apresentados acima, o **hit rate** permanecerá em **0,5**, pois a cache possui apenas 1 bloco, capaz de armazenar apenas dois elementos do vetor.  

Para qualquer vetor com tamanho maior que 2, cada varredura pelo vetor (**Rep Count**) resultará em um padrão fixo: uma iteração que causa um **miss**, seguida por uma iteração que causa um **hit** (o elemento seguinte foi carregado na memória após o miss). Esse comportamento se mantém independentemente do número de repetições, resultando consistentemente em um **hit rate de 0,5**.  

---

## Cenário 2

### Perguntas:

**Qual combinação de parâmetros está produzindo o hit rate observado? Pense sobre os valores de cada parâmetro.**  
**Parâmetros do Programa:**  
- Tamanho do Array: 128 bytes  
- Step Size: 27  
- Rep Count: 2  
- Opção: 0 (apenas escrita)  

**Parâmetros da Cache:**  
- Níveis de Cache: 1  
- Tamanho do Bloco: 8  
- Número de Blocos: 1  
- Política de Posicionamento: Mapeamento Direto  
- Política de Substituição de Bloco: LRU  

A cache possui apenas 1 bloco neste cenário, capaz de armazenar apenas 2 elementos do vetor. Com um **Step Size = 27** e um tamanho de vetor de 32 elementos, na primeira varredura pelo vetor, cada iteração resulta em um **miss**, já que o passo é maior do que a quantidade de elementos que a cache pode conter.  

Ao acessar o primeiro elemento do vetor, ocorre um **miss**, e os dois primeiros elementos são carregados no bloco da cache devido à política de **write-allocate**. O próximo acesso gera outro **miss**, onde são carregados o vigésimo sétimo e vigésimo oitavo elementos do vetor.  

No início da segunda varredura, os dados na cache são o vigésimo sétimo e vigésimo oitavo elementos do vetor, mas os dados buscados terão que ser novamente carregados na cache. Isso recria a mesma situação da primeira varredura, onde todos os acessos também geram **misses**. Portanto, o **hit rate** é **0**, já que não há acessos atendidos pela cache.  

**O que acontece com o hit rate se aumentarmos o número de blocos e por quê?**  
Para qualquer cache com mais de 1 bloco, haverá 2 **misses** e 2 **hits**. As faltas ocorrem durante a primeira varredura pelo vetor, quando o início do vetor é acessado, gerando um **miss**. O primeiro e segundo elementos são então carregados na cache.  

Na segunda varredura, como os blocos da cache já contêm os valores necessários, cada acesso resulta em um **hit**. O **hit rate** é de **0,5**, já que metade dos acessos foram **hits**.  

---

## Cenário 3

### Perguntas:

**Escolha um número de blocos maior do que 1 e determine o menor tamanho do bloco que usa todos os blocos *e* maximiza o hit rate dado os parâmetros abaixo. Explique o por quê.**  

**Parâmetros do Programa:**  
- Tamanho do Array: 256 bytes  
- Step Size: 2  
- Rep Count: 2  
- Opção: 1 (escrita e leitura a cada iteração)  

**Parâmetros da Cache:**  
- Níveis de Cache: 1  
- Tamanho do Bloco: 32  
- Número de Blocos: 4  
- Política de Posicionamento: Mapeamento Direto  
- Política de Substituição de Bloco: LRU  

Usando esses parâmetros, cada bloco pode armazenar **8 elementos** do vetor, pois cada elemento é um inteiro de 4 bytes e cada bloco tem tamanho de 32 bytes (**32 / 4 = 8 elementos**). Os 4 blocos da cache conseguem conter todos os 64 elementos do vetor neste cenário.  

Na **primeira varredura**, cada **miss** carrega um bloco com 8 elementos, mas devido à política de escrita e leitura a cada iteração (**Opção = 1**), ocorrem **hits** logo após o carregamento. Na **segunda varredura**, todos os elementos já estão na cache, resultando em **hits** em todas as operações.  

O **hit rate** neste cenário é **0,875**, o maior possível para o menor tamanho de bloco (8 elementos) em uma cache de 4 blocos.  

# Exercício 3
* Ordene as funções da mais rápida para a mais lenta e explique por que a classificação de cada função faz sentido com base no seu entendimento de como a cache funciona. Algumas funções podem ter tempos de execução similares. Se for esse o caso, explique por quê.

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

