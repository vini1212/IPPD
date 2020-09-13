import java.rmi.ConnectException;
import java.rmi.Naming;

public class FiboCliente {
  public static void main(String[] args) {
    Integer n = 10, r;
    Fibonacci f; // (1)
    try {
     n = Integer.parseInt(args[0]);
     if( (n < 2) || (n >35) ) throw new Exception();
    } catch( Exception e ) {
      System.out.println("Decidí calcular Fibo de 20.");
      n = 20;
    }
 
    try {
      f = (Fibonacci) Naming.lookup("rmi://127.0.0.1:1099/Fibonacci"); // (2)
      r = f.calcula(n); // (3)
      System.out.println("Fibonacci de " + n + " = " + r);
    } catch (ConnectException e) {
      System.out.println("ERRO: Servidor Desconectado");
    } catch (Exception e) {
      System.out.println("Erro Interno");
    }
  }
}

/*
(1) Uma referência local ao serviço desejado.

(2) Retorna a referência a um stub para o objeto remoto. Toda a identificação do serviço desejado deve ser apresentada (o host, a porta e o nome fantasia).

(3) A invocação é feita no stub, resposável por invocar o serviço remoto.
*/
