# COMCS - 13 de outubro de 2026

1.1 Sliding Window - continuacao da aula anterior|
**Sliding window**

A ideia apresentada e que o transmissor nao envia indefinidamente. Existe uma janela que determina quantas frames/mensagens podem estar em transito sem ainda terem sido confirmadas.

Exemplo usado pelo professor:

. Tmanho da janela = 5

. Transmissor pode enviar primeiro 5 mensagens;

. nao pode simplesmente continuar com a sexta;

. quando chega um ACK, a janela pode avancar;

. passa entao a existir espaco para enviar outra frame.

>  Variaveis 

. Sending Window Size - SWS

. numeros de sequencia

. identificacao da ultima frame envidada;

. identificacao da ultima frame reconhecida.

**Ideia Visual**


Sender

[1][2][3][4][5]  6  7  8 ...
 └──── window ────┘

          ↓ ACK

   [2][3][4][5][6]  7  8 ...
      └── window ──┘

A janela desliza quando chegam acknowledgements.
Um ACK pode ainda permitir que a janela avance mais de uma posicao, dependendo do mecanismo de acknowledgement utilizado. 



---

# 1.3 Latencia, perda e comunicacao de voz

Nem sempre retransmitir e melhor.

Em aplicacoes de voz, esperar pela retransmissao d eum poacote perdido pode introduzir atraso prejusiciall a comunicacao.
A aula refere que a partir de determinado atraso - foi mencionado aproximadamente 200 ms -- comecamos a perceber que a conversacao nao esta natural.
