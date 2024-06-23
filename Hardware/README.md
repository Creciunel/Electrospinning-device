# Electrospinning Device based on Arduino Mega

## High voltage result and schematics

### Reult

<p> The result of the electrospinning process is accesible on link below. </p>
<a href="https://docs.google.com/spreadsheets/d/1FEkuDaI_2rEFF1M06S9z06Yd7cQ-smT4pYeCvJsIN_U/edit?usp=sharing">Value on testing process</a>

### Schematics

## Hardware Connection

<table style="border: none;">
  <tr>
    <h3>Display</h3>
    <!-- display charaters -->
    <ul>
        <li> Examples of <a href="https://github.com/WeActStudio/WeActStudio.TFT-LCD-Module/tree/master/Examples">code</a> </li>
        <li> <a href="https://github.com/WeActStudio/WeActStudio.TFT-LCD-Module">WeActStudio.TFT-LCD-Module</a> </li>
    </ul>
    <td style="border: none; text-align: left;">
      <img src="/Images/Display.webp" alt="Display" width="300px">
      <img src="/Images/displayPins.png" alt="pinout" width="300px">
      <!-- https://github.com/WeActStudio/WeActStudio.TFT-LCD-Module -->
      <table>
        <tr>
            <th>Arduino Pins</th>
            <th>ILI9341 Pins</th>
            <th></th>
            <th>Arduino Pins</th>
            <th>TouchScreen Pins</th>
        </tr>
        <tr>
            <td>3.3V or 5V</td>
            <td>VCC</td>
            <td></td>
            <td>13</td>
            <td>TSCK (SCK)</td>
        </tr>
        <tr>
            <td>GND</td>
            <td>GND</td>
            <td></td>
            <td>14</td>
            <td>TCS (CS)</td>
        </tr>
        <tr>
            <td>6</td>
            <td>BL</td>
            <td></td>
            <td>15</td>
            <td>TMOSI (MOSI)</td>
        </tr>
        <tr>
            <td>7</td>
            <td>RES</td>
            <td></td>
            <td>12</td>
            <td>TMISO (MISO)</td>
        </tr>
        <tr>
            <td>12</td>
            <td>SDO (MISO)</td>
            <td></td>
            <td>17</td>
            <td>TPEN (Touch Interrupt)</td>
        </tr>
        <tr>
            <td>11</td>
            <td>SDA (MOSI)</td>
            <td></td>
            <td>GND</td>
            <td>GND</td>
        </tr>
        <tr>
            <td>8</td>
            <td>D/C</td>
            <td></td>
            <td></td>
            <td></td>
        </tr>
        <tr>
            <td>13</td>
            <td>SCL (SCK)</td>
            <td></td>
            <td></td>
            <td></td>
        </tr>
        <tr>
            <td>9</td>
            <td>CS</td>
            <td></td>
            <td></td>
            <td></td>
        </tr>
        <tr>
            <td>Not connected</td>
            <td>FM</td>
            <td></td>
            <td></td>
            <td></td>
    </table>
 <!-- <table>
    <tr>
          <th>Arduino Pins</th>
          <th>ILI9341 Pins</th>
        </tr>
        <tr>
          <td>53</td>
          <td>TFT_CS</td>
        </tr>
        <tr>
          <td>46</td>
          <td>TFT_DC</td>
        </tr>
        <tr>
          <td>51</td>
          <td>TFT_MOSI</td>
        </tr>
        <tr>
          <td>52</td>
          <td>TFT_SCLK</td>
        </tr>
        <tr>
          <td>47</td>
          <td>TFT_RST</td>
        </tr>
        <tr>
          <th>Arduino Pins</th>
          <th>TouchScreen Pins</th>
        </tr>
        <tr>
          <td>A14</td>
          <td>YP</td>
        </tr>
        <tr>
          <td>A15</td>
          <td>XM</td>
        </tr>
        <tr>
          <td>48</td>
          <td>YM</td>
        </tr>
        <tr>
          <td>49</td>
          <td>XP</td>
        </tr>
      </table> -->
    </td>
  </tr>

  <tr>
    <h3>Motor</h3>
    <td style="border: none; text-align: left;">
      <img src="/Images/L293DArduinoShieldPinouts.png" alt="L293D Motor Driver Shield" width="300px">    
      <table>
        <tr>
          <th>Arduino Pins</th>
          <th><a href="https://github.com/adafruit/Adafruit_Motor-Shield-v1/blob/master/mshieldv12schem.png">L293D Motor Driver Shield</a></th>
          <th></th>
          <th>Motor sheld sheft registers 74HCT595</th>
          <th>Pin</th>
        </tr>
        <tr>
          <td>11</td>
          <td>Motor 1</td>
          <td></td>
          <td>MOTOR1_A</td>
          <td>2</td>
        </tr>
        <tr>
          <td>3</td>
          <td>Motor 2</td>
          <td></td>
          <td>MOTOR1_B</td>
          <td>3</td>
        </tr>
        <tr>
          <td>5</td>
          <td>Motor 3</td>
          <td></td>
          <td>MOTOR2_A</td>
          <td>1</td>
        </tr>
        <tr>
          <td>6</td>
          <td>Motor 4</td>
          <td></td>
          <td>MOTOR2_B</td>
          <td>4</td>
        </tr>
        <tr>
          <td>9</td>
          <td>Servo 1</td>
          <td></td>
          <td>MOTOR3_A</td>
          <td>5</td>
        </tr>
        <tr>
          <td>10</td>
          <td>Servo 2</td>
          <td></td>
          <td>MOTOR3_B</td>
          <td>7</td>
        </tr>
        <tr>
          <td>4, 7, 8, 12</td>
          <td>Shift registers</td>
          <td></td>
          <td>MOTOR4_A</td>
          <td>0</td>
        </tr>
        <tr>
          <td>2 and 13, Analog A0 to A5</td>
          <td>Not Connected</td>
          <td></td>
          <td>MOTOR4_B</td>
          <td>6</td>
        </tr>
      </table>


### ADC Analog-to-Digital Converter

It is connected to pin A8 or as number 62.
