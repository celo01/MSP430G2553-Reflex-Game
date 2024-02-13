# MSP430G2553-Reflex-Game
A simple reflex game is played in this system that I created with the MSP430G2553 card.

TR|
MSP430G2553 kartıyla oluşturduğum bu sistemde basit bir refleks oyunu oynanmaktadır.
Bu oyunda 1 adet MSP430G2553 Kartı, 1 adet 16x2 LCD ekran, 4 adet push-buton, 3 adet led (sarı, kırmızı ve yeşil renkli) ve 1 adette potansiyometre kullandım.
Oyun basit olarak şu şekilde çalışmaktadır. Lcd Ekrandaki yazıya göre oyun başlar. 
Rastgele bir led yanar(kırmızı veya yeşil). Hangi renk led yandıysa o lede bağımlı butona hangi oyuncu ilk basarsa roundu kazanır.
Oyun 5 rounddan oluşmakta, 3 round kazanan oyunu da kazanmış olur.
Bunların yanı sıra oyunda 15 saniye boyunca herhangi bir input olmazsa sistem kendini MSP430 Kartlarına özel olan düşük güç moduna (LPM4) çekmektedir.

Herhangi bir sorun varsa, bana yazmaktan çekinmeyin!



EN|
A simple reflex game is played in this system that I created with the MSP430G2553 card.
In this game, I used 1 MSP430G2553 Card, 1 16x2 LCD screen, 4 push-buttons, 3 LEDs (yellow, red and green colors) and 1 potentiometer.
The game works simply like this. According to the text on the LCD Screen, the game starts. 
A random led lights up(red or green). Whichever color led is lit, whichever player presses the dependent button on that led first wins the round.
The game consists of 5 rounds, the winner of 3 rounds also wins the game.
In addition, if there is no input for 15 seconds in the game, the system pulls itself into low power mode (LPM4), which is special for MSP430 Cards.

If there is any problem, do not hesitate to write to me!

