import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Fibonacci // (1)
                 extends Remote { 
  public Integer calcula( Integer n ) throws RemoteException;
}

/*
(1) Esta classe define a interface do serviço proposto.
*/

