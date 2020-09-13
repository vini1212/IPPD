import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class FiboImplementacao // (1)
             extends UnicastRemoteObject implements Fibonacci {
public FiboImplementacao() throws RemoteException {
    super(); // (2)
  }
  static private int fiboSeq( int n ) {
   if( n < 2 ) return n;
   else return fiboSeq(n-1)+fiboSeq(n-2);
  }
  public Integer calcula( Integer n ) throws RemoteException {
    System.out.println("Oba! Trabalho! Vou calcular o Fibo(" + n + ")");
    return fiboSeq(n);
  }
}

/*
(1) Esta classe implementa efetivamente o serviço. Ela deve implementar a interface definida pela aplicação (Fibonacci, no caso) e estender UnicastRemoteObject, que associa o objeto ao sistema RMI. Como consequência, o construtor deste objeto deve retornar uma exceção RemoteException em caso de problema. Observe que, fora a particularidade de herdar de UnicastRemoteObject, trata-se de uma classe como qualquer outra, podendo conter tantos métodos e atributos quanto for necessário na aplicação. A dificuldade estará em parametrizar o construtor, caso necessário.

(2) O construtor da classe UnicastRemoteObject precisa ser invocado.

(3) Esta é a implementação do serviço indicado (também sinaliza uma exceção em caso de erro). O skeleton do lado do servidor é responsável por desempacotar os parâmetros de entrada e empacotar o respectivo retorno.
*/
