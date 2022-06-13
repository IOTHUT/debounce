#define pino_botao      4  // pino para leitura digital
#define tempo_debounce  50 // tempo em ms para o debounce (voce pode aumentar ou diminuir esse valor para testes)


// variaveis
boolean ultimoEstadoValidado        = LOW;       // ultimo estado valido
boolean ultimoEstadoVariante        = LOW;       // ultimo estado que variou
boolean estadoAtual                 = HIGH;      // estado atual do botao
unsigned long debounceCounter       = 0;         // salva ultima vez em que o botao foi acionado

void setup() {
  Serial.begin(115200);           
  while(!Serial);
  pinMode(pino_botao, INPUT_PULLUP);
}

void loop() {

  estadoAtual = digitalRead(pino_botao);    //le o estado do botao a cada ciclo do loop
  
  // se o estado atual for diferente do ultimo estado que variou (bouncing)
  if(estadoAtual != ultimoEstadoVariante){
    debounceCounter = millis();           //atualiza tempo (reseta variavel para o tempo atual)        
    ultimoEstadoVariante = estadoAtual;   //atualiza estado da variavel auxiliar para detectar as variacoes de tensao
  }

  // caso tenha pressionado (ou solto) o botao por um tempo maior que o definido para debounce 
  if((millis() - debounceCounter) > tempo_debounce){
    
    //-----------------------------------------------------------------------------
    // checa se o botao foi pressionado ou solto (diferente do ultimo estado valido)
 
    if(ultimoEstadoValidado == HIGH && estadoAtual == LOW) Serial.println("botão pressionado");
    else if(ultimoEstadoValidado == LOW && estadoAtual == HIGH) Serial.println("botão solto");
      
    //-----------------------------------------------------------------------------
    
    ultimoEstadoValidado = estadoAtual;    // atualiza ultimo estado valido
  }//end if debounceCounter
  
} //end void loop
