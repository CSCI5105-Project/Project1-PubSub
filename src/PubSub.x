


program PubSub {
	version VERSION {
		int join(string IP, int Port) = 1;
		int leave(string IP, int Port) = 2;
		int subscribe(string IP, int Port, string Article) = 3;
		int unsubscribe(string IP, int Port, string Article) = 4;
		int publish(string IP, int Port, string Article) = 5;
		int ping() = 6;
	} = 1;

}=0x20406080;
