# RPC Fibonacci

Nesse diretório estão direcionados os arquivos para implemnetação do servidor/cliente a partir da programação paralela RPC

## Executando os códigos
```
rpcgen fibonacci.x
gcc cliente.c fibonacci_xdr.c fibonacci_clnt.c -o cliente
gcc servico.c fibonacci_xdr.c fibonacci_svc.c -o servidor
./servidor // Para terminal 1
./cliente localhost 5 // Para o terminal 2 calculando o fibonacci de 5
```