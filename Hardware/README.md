# Electrospinning Device based on Arduino Mega

Arduino Mega pinout is  
<img src="/Images/Arduino-Mega-Pinout.jpg" alt="Arduino Mega pinout" width="300px">

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
      <!-- <table>
        <tr>
            <th>Arduino Pins</th>
            <th>ILI9341 Pins</th>
        </tr>
        <tr>
            <td>3.3V or 5V</td>
            <td>VCC</td>
        </tr>
        <tr>
            <td>GND</td>
            <td>GND</td>
        </tr>
        <tr>
            <td>6</td>
            <td>BL</td>
        </tr>
        <tr>
            <td>7</td>
            <td>RES</td>
        </tr>
        <tr>
            <td>12</td>
            <td>SDO (MISO)</td>
        </tr>
        <tr>
            <td>11</td>
            <td>SDA (MOSI)</td>
        </tr>
        <tr>
            <td>8</td>
            <td>D/C</td>
        </tr>
        <tr>
            <td>13</td>
            <td>SCL (SCK)</td>
        </tr>
        <tr>
            <td>9</td>
            <td>CS</td>
        </tr>
        <tr>
            <td>Not connected</td>
            <td>FM</td>
        </tr>
        <tr>
            <th>Arduino Pins</th>
            <th>TouchScreen Pins</th>
        </tr>
        <tr>
            <td>13</td>
            <td>TSCK (SCK)</td>
        </tr>
        <tr>
            <td>14</td>
            <td>TCS (CS)</td>
        </tr>
        <tr>
            <td>15</td>
            <td>TMOSI (MOSI)</td>
        </tr>
        <tr>
            <td>12</td>
            <td>TMISO (MISO)</td>
        </tr>
        <tr>
            <td>17</td>
            <td>TPEN (Touch Interrupt)</td>
        </tr>
        <tr>
            <td>GND</td>
            <td>GND</td>
        </tr>
    </table> -->
 <table>
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
      </table>
    </td>
  </tr>

  <tr>
    <h3>Motor</h3>
    <td style="border: none; text-align: left;">
      <img src="/Images/L293DArduinoShieldPinouts.png" alt="L293D Motor Driver Shield" width="300px">    
      <table>
        <tr>
          <th>Arduino Pins</th>
          <th>L293D Motor Driver Shield</th>
        </tr>
        <tr>
          <td>11</td>
          <td>Motor 1</td>
        </tr>
        <tr>
          <td>3</td>
          <td>Motor 2</td>
        </tr>
        <tr>
          <td>5</td>
          <td>Motor 3</td>
        </tr>
        <tr>
          <td>6</td>
          <td>Motor 4</td>
        </tr>
        <tr>
          <td>9</td>
          <td>Servo 1</td>
        </tr>
        <tr>
          <td>10</td>
          <td>Servo 2</td>
        </tr>
        <tr>
          <td>4, 7, 8, 12</td>
          <td>Shift registers</td>
        </tr>
        <tr>
          <td>2 and 13, Analog A0 to A5</td>
          <td>Not Connected</td>
        </tr>
      </table>
    </td>
  </tr>
</table>

### ADC Analog-to-Digital Converter

It is connected to pin A8 or as number 62.
