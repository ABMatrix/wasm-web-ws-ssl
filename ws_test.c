extern void wsConnect(char *address);     
extern void wsSend(char *message);     
extern void wsClose();     
extern void print(char *message);      
char buffer[100];     
char *getBuffer(){ return buffer; }      
void wsOnMessage(){
           print("received message");       
           print(buffer);       
           wsClose();       
           print("connection closed");     
}      
void wsOnOpen(){       
    print("connected");       
    wsSend("Hello WebAssembly !");     
}       
void test(){
    print("connecting...");  
    wsConnect("ws://192.168.31.131:8888");       
    print("connecting...");     
} 
