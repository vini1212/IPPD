Exemplo RMI Java - Cálculo de Fibonacci

O serviço é realizado por uma instância da classe FiboImplementacao, contido no arquivo FiboImplementacao.java. O cliente, implementado no corpo do método main da classe FiboCliente, invoca o serviço oferecido. A interação é possível graças ao uso de uma interface, visível no lado do cliente e implementada no lado do servidor. Esta interface está no arquivo Fibonacci.java.

Conteúdo do diretório:

- FiboCliente.java: o código do cliente.
- FiboImplementacao.java: o código da classe que computa Fibonacci.
- Fibonacci.java: especificação do serviço oferecido em termos de uma interface.Observe que o nome escolhido para esta classe representa a operação desejada.
- FiboServidor.java: criação do objeto que computa o serviço e registro do nome do serviço oferecido.

Obtenha os executáveis:
%> javac *.java

Se compilou, ótimo. Então siga os passos para execução. Utilize três terminais para poder visualizar os três passos envolvidos na execução.

Passo 1: Inicializar a porta desejada no host corrente para receber invocações TMI. O comando a ser dado, em um dos terminais, é:
%> rmiresgistry
A porta default é a 1099. Caso seja desejado outra porta, informar como parâmetro. Este comando, caso tenha executado com sucesso, não irá retornar o prompt. Não é necessário estar, efetivamente em rede!

Passo 2: Lançar o servidor propriamente dito em outro terminal. No caso do nosso exemplo, executando o seguinte comando:
%> java -Djava.security.policy=policy FiboServidor
Este comando também não retorna. Alias, este exemplo tem um pequeno "furo", o servidor não finaliza nunca a execução... (CTR-C nele!) O parâmetro de lançamento indica um arquivo que contém as políticas de liberação das portas para acesso no host corrente.

Passo 3: Lançar o cliente no terceiro terminal:
%> java FiboCliente
Ao contrário dos demais, este faz sua execução e retorna ao prompt.


