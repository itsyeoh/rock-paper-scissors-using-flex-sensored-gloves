# Rock-Paper-Scissors-using-Flex-Sensored-Gloves

CS 362 Spring 2019

Jason Yeoh (jyeoh2) x Ho Chon (hchon6)

## Abstract
Why play rock-paper-scissor the normal way when you can upgrade it to have a better experience? Using flex sensing technology and an inter-integrated Arduino circuit, it would increase the fun in playing a simple game. The timer countdown can be used to prevent cheating and it would light up corresponding to a victory or loss. The winner would even get its own victory tune, improving winning experience. 

## Detailed Project Ideas
### Details Project Description
#### Information of Project as a Whole
The idea of this project is play a game of rock-paper-scissors with a flex glove. The flex glove is connected with two flex sensor strips. The Arduino receives the glove’s input and would output the appropriate response. The response are the LEDs, the LCD display, and the buzzer. The winner would have the Green LED light, a winner text, and a buzzer tone. While the loser will have the Red LED light. A tie game would only have each players yellow LED light up. The button will either start or quit the game, and the 16x2 LCD display would keep track of the score and will be displayed on a box that would keep everything, but the gloves together. 

#### Information of the Sub-Parts of your Project
Our project will follow a Master Writer/Slave Receiver configuration via an I2C synchronous serial protocol. The Master Writer will be programmed to (a) store in all sensor readings, (b) identify user picks, (c) compare and evaluate the results, (d) display the results in the LCD screen and (e) tally in the scores. On the other hand, the slave receiver counterpart will work on the peripheral components such as LEDs, buzzers and pushbuttons. 

### Project Design including Expected Inputs/Outputs
For this project, we plan to make a Rock-Paper-Scissors game using two Arduino Unos which will communicate via an inter-integrated circuit. The project will use resistance-based flex sensor strips (attached at the middle and ring fingers of the player’s glove) to recognize user gestures. Buzzers will serve as a countdown signal for the user to decide on their option. There would be a 3-second delay for the user to decide on their selection. The tally of scores and countdown will be displayed on the 16x2 LCD display. Also, we will have 6 LEDs to reveal the winner or loser in a particular round. If the player wins the round, a green LED will light up, if the player loses the round, a red LED to light up, if the players tie, then the yellow LED lights up. There will be a button to start the game. Once started, the game will continue for 3 rounds. Once a player has won more rounds than the other player, the LCD display will congratulate the player who won and offer a “Start Game” or “Quit Game” option. To choose either method, we have placed two buttons. The first button indicates to end the game, showing a game over screen on the LCD display. While, the other button would reset the game and start over. This button data is sent from the Slave arduino to the Master arduino.

### Communication Details for inter-Arduino Communication
To connect the two Arduinos, we plan on making an I2C bus between two Arduinos. Both Arduino’s A4 and A5 pin will connect with each other as well as the Ground. In our Code, we have to use void receiveEvent(int) to share the given inputs between Arduinos. The two arduinos will use the master/slave code and share information with Serial.read() and Serial.write(). One arduino will be the master code, which will contain the flex sensors and LCD display. The second arduino will be the slave code, which will operate all the other components, such as the buzzer, LED, and button. The master code will have values of the flex sensors and convert it into define values of rock, paper, or scissors. It will then compare it to player one to player two and then determine the outcome of the game. It will also update the LCD screen with the appropriate text. The outcome will be sent to the slave code to function accordingly. The slave code will light up LED’s according to the outcome of the game. It will also control the button and buzzer. The button starts the game, while the buzzer is the countdown to pick your move. The buzzer would play a Mario soundtrack during the 3 second delay of the count down to eliminate the long silence while waiting for the next round. 

## Description of the original work being attempted by your project
Project Link: https://grathio.com/2010/03/rock_paper_scissors_training_glove/

This original work is by Steve Hoefer from Grathio Labs. He made a single player rock-paper-scissor game versus an AI. The AI is represented by three polyester sheets, which were laser-cut and combined with various color LEDs. The AI’s decision would then show on the light up sheets. He used an accelerometer to start his game. He then put it all together into a single glove. 
The major differences between our projects is that rather than an AI, we have two players. Also to start our game, we have buttons that connect with LEDs and a buzzer to tell you when to pick a hand.
