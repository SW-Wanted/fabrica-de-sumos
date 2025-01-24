# Fábrica de Sumos 🍹

**Exame de Estrutura de Dados I**  
Este projeto simula o funcionamento de uma fábrica de sumos, utilizando conceitos de estruturas de dados. Escrito em C, o programa demonstra a manipulação eficiente de filas, validação de dados e outros conceitos fundamentais.

---

## 🥇 Objectivos
- Dominar os conceitos sobre estruturas de dados
- Materializar os conceitos por meio de uma solução prática
- Melhorar capacidade de interpretação de texto, escrita e oratória
---

## 📚 Índice
- [📖 Introdução](#-introdução)
- [✨ Funcionalidades](#-funcionalidades)
- [✈️ Implementação](#-implementação)
- [🚀 Instalação](#-instalação)
- [🛠️ Como Usar](#-como-usar)
- [🤝 Contribuições](#-contribuições)
- [🎓 Universidade](#-isptec---instituto-superior-politécnico-de-tecnologia-e-ciências)

---

## 📖 Introdução
Uma fábrica de enchimento de sumos precisa de comprar novas máquinas para a sua produção. Antes da compra, o concelho de administradores decidiu mandar desenvolver uma simulação para aferir o nível da produção. A simulação consiste no seguinte:

-  A fábrica enche 2 tamanhos diferentes de pacotes de sumo. O de 200 ml (PA) e o de 1 L (PB). Existem 2 filas para cada pacote, representando cada uma das fases do processo. A primeira fila é do enchimento e a segunda do embalamento. Cada fila está associada a uma máquina;
-  Uma máquina de produção (enchimento, embalamento e empilhamento) deverá ser representada por um TAD que possui o nome, tipo de máquina, tempo de processamento, a quantidade de unidades processadas num dia de produção, a fila de produtos a serem processados e outros atributos que sejam necessários;
-  Os pacotes são inseridos na fila inicial (uma fila para cada tipo de pacote);
-  Os pacotes do tipo PA (200 ml) saem da fila e entram para a máquina de enchimento. Depois do enchimento, os pacotes seguem em fila para a máquina de embalamento num conjunto de 6. Enquanto não houver 6 pacotes na máquina, não é possível fazer o embalamento. Depois de sair da máquina, já agrupados em 6 as embalagens são empilhadas. A máquina empilha até 4 caixas de 6 cada;
-  Os pacotes do tipo PB (1 L) seguem o mesmo processo do PA, com a diferença de que serão embalados em grupos de 4 e empilhadas até 3 caixas;
-  Cada pacote tem características próprias para que seja considerado em condições para ser embalado. Caso um pacote esteja fora do padrão (tipo ou peso errado) é descartado da fila e não entra na máquina de embalamento o que constitui um prejuízo na produção.

---

## ✨ Funcionalidades
1. **Inserir pacote na fila**
- **Automática**: Permite ler a partir de um ficheiro de dados uma lista de pacotes (PA e PB) e inseri-los nas filas apropriadas.
- **Manual**: Permite solicitar a informação sobre um pacote ao utilizador e inseri-lo na fila apropriada. O pacote deve ter o tipo, o peso e outros atributos que sejam necessários.
2. **Encher**
- Remove os pacotes de uma das filas iniciais e entram para a máquina de enchimento. Cada máquina deve respeitar o tempo determinado para encher os pacotes. Enquanto a máquina estiver ocupada, o pacote seguinte irá continuar em espera. Depois de encher o pacote é inserido na fila de embalamento apropriada.
3. **Validar produto**
- Percorre todos os pacotes que estão numa das filas de embalamento e verifica se existe algum fora do padrão. (Verifica se o enchimento está correcto ou se o pacote está na fila certa). Caso haja algum problema, deve ser removido da fila e contabilizado como prejuízo.
4. **Encaminhar**
-  Permite remover um produto válido da fila de embalamento e encaminhá-lo para a máquina apropriada até agrupar a quantidade definida por cada tipo (6 para PA e 4 para PB). Depois de atingir o limite, não é possível encaminhar pacotes adicionais;
5. **Embalar & Empilhar**
- Permite criar uma embalagem de pacotes da quantidade definida por cada tipo. Se a quantidade de pacotes existentes na máquina for inferior ao definido, o embalamento não é efectuado. Depois do embalamento, o pacote é empilhado até ao limite definido por cada tipo. Se a pilha estiver atingido o limite, nova pilha é criada.
6. **Imprimir**
- Fila de enchimento
- Fila de embalamento
- Número de pilhas
7. **Terminar simulação**
- No final da simulação deve ser gerada a seguinte informação em 
ficheiros:
  - quantidade de produto embalado de cada tipo e o total;
  -  quantidade de produto descartado de cada tipo total;
  -  lucro previsto por tipo de pacote;
  -  prejuízo por tipo de pacote.
- Depois de gerar os relatórios, as estruturas criadas serão 
destruídas. Se o utilizador desejar, pode iniciar uma nova 
simulação.
8. **Sair** -  Termina o programa
---

## ✈️ Implementação
Faça um programa que implemente a simulação proposta tendo em conta a 
informação abaixo, sabendo que o Lucro = Venda – custo e Prejuízo se Lucro < 0:

| Produto | Custo de produção (KZ) | Preço de venda (KZ) |
|---------|-------------------------|---------------------|
| PA      | 250                     | 1100                |
| PB      | 220                     | 1700                |
---

## 🚀 Instalação
1. Clone o repositório:
   ```bash
   git clone https://github.com/SW-WANTED/fabrica-de-sumos.git
   ```
2. Entre no diretório:
   ```bash
   cd fabrica-de-sumos
   ```

---

## 🛠️ Como Usar
O programa oferece um menu interativo com as seguintes opções:

1. **Inserir Pacote**: Adicione manualmente um pacote à fila.
2. **Validar Pacotes**: Verifique se os pacotes estão dentro dos padrões.
3. **Processar Fila de Enchimento**: Movimente pacotes de fila.
4. **Relatórios**: Exiba os dados de produção e resultados.
5. **Encerrar Simulação**: Finalize o programa.

---

## 🤝 Contribuições
1. Faça um fork deste repositório.
2. Crie uma branch para sua funcionalidade:
   ```bash
   git checkout -b feature/nova-funcionalidade
   ```
3. Envie seu código:
   ```bash
   git commit -m "Descrição da funcionalidade"
   git push origin feature/nova-funcionalidade
   ```
4. Abra um pull request no GitHub.

---

## 🎓 ISPTEC - Instituto Superior Politécnico de Tecnologia e Ciências

- **Site oficial**: [isptec.co.ao](https://www.isptec.co.ao)
- **Localização**: Luanda, Angola

### 🧑‍🏫 Professor (a):
Este projeto foi elaborado pela professora:
- **Sílvia António**: [Email institucional](mailto:silvia.antonio@isptec.co.ao)

### ✨ Estudantes
Este projeto foi desenvolvido por:
- <a href="https://github.com/SW-Wanted"><img src="https://github.com/SW-Wanted.png" alt="Emanuel dos Santos" width="25" height="25" align="center"> Emanuel dos Santos</a>
- <a href="https://github.com/Carlos-Tchipia"><img src="https://github.com/Carlos-Tchipia.png?size=50" alt="Carlos Tchípia" width="25" height="25" align="center"> Carlos Tchípia</a>
- <a href="https://github.com/Abel0207"><img src="https://github.com/Abel0207.png?size=50" alt="Abel Canas" width="25" height="25" align="center"> Abel Canas</a>
---
