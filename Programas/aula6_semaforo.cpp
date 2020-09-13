int buff[TAM];
int nbelem;
mutex m;
semaforo s(0);
semaforo s1(TAM);

//ut Produtora
while( notEnd ){
	p(s1)
	lock(m);
	insereElem(buff);
	++nbelem;
	unlock(m);
	v(s)
}

//ut Consumidora
while( notEnd ){
	p(s);
	lock(m);
	retiraElem(buff);
	--nbelem;
	unlock(m);
	v(s1)
}