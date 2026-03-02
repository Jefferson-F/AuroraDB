# AuroraDB

**Um SGBD relacional com propósitos educacionais.**

O AuroraDB nasceu da curiosidade de entender os internals de um Sistema Gerenciador de Banco de Dados e evoluiu para o meu Trabalho de Conclusão de Curso. Desenvolvido do zero em C++17, o projeto foca intencionalmente no núcleo de um banco de dados: o motor de armazenamento e a implementação de estratégias de acesso.

## Aprendizados
Toda a construção até o estado atual do projeto me direcionou por diversos problemas, os quais tive que pesquisar e entender para conseguir construir uma solução adequada.

### PageManager

A construção do PageManager (camada de interação com o disco do AuroraDB) exigiu um aprofundamento na forma como o C++ gerencia memória e arquivos binários.

* Problema: Ao tentar mapear os dados da memória (armazenados em uma `struct` fixa) diretamente para o arquivo binário em disco, ocorriam inconsistências de tamanho. Ao ler o arquivo de volta, dados corrompidos eram retornados.
* Causa: O compilador estava aplicando struct padding, inserindo bytes na estrutura para alinhar a memória e otimizar a leitura pela CPU. Esses bytes extras estavam sendo indevidamente persistidos no disco.
* Solução: Em vez de gravar a estrutura bruta, implementei rotinas de serialização e desserialização. Isso garantiu o controle exato dos bytes escritos e lidos no arquivo binário, ignorando o padding da memória e garantindo a consistência dos dados do banco. Isso foi importante pois, simplesmente "desligar" o padding do compilador, embora possível, não é recomendado.

### BufferPoolManager

Um SGBD precisa gerenciar seu próprio cache, pois as estratégias do Sistema Operacional não são otimizadas para cargas de trabalho de banco de dados. Para resolver isso, desenvolvi um `BufferPoolManager` utilizando a política de substituição.

Para garantir alta performance e acesso em $O(1)$, a arquitetura do cache não se limita às duas estruturas convencionais, mas sim a uma sincronização complexa de quatro componentes:

* Vetor: Armazena as páginas carregadas do disco na memória.
* Pilha: Rastreia de forma eficiente as posições livres no vetor.
* Lista Duplamente Encadeada: Ordena as páginas da mais recentemente usada para a menos usada (LRU).
* HashMap: Mapeia os IDs das páginas para seus nós na lista, permitindo buscas em tempo constante.

Desafios Técnicos e Otimizações:
Orquestrar o ciclo de vida dessas quatro estruturas em C++17 foi um verdadeiro teste de gerenciamento de memória. Solucionar bugs complexos de Double Free, vazamento de memória e corrupção de Heap foi o que garantiu a estabilidade do Storage Engine. 



Para elevar o desempenho do motor, implementei as seguintes estratégias:
* Redução de Overhead: Identifiquei um gargalo onde o sistema movia páginas de 4KB na memória durante as atualizações do LRU. Otimizei o processo armazenando na lista encadeada apenas os índices do vetor.
* I/O Eficiente: Adicionei o controle de dirty flags para rastrear modificações, garantindo que apenas as páginas alteradas sejam reescritas no disco.
* Proteção de Páginas: Implementei a lógica de pins, impedindo que o algoritmo de substituição remova da memória uma página que ainda está sendo utilizada pelo banco.
