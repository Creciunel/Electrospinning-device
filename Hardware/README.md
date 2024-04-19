<h1>Electrospinning Device based on Arduino Mega</h1>

<p>Arduino Mega pinout is</p>
<img src="/Images/Arduino-Mega-Pinout.jpg" alt="Arduino Mega pinout" style="max-width: 100%;">

<h2>Hardware Connection</h2>
<table style="border: none;">
    <tr>
        <td style="border: none; text-align: left;">
            <h3>Display</h3>
            <!-- https://github.com/WeActStudio/WeActStudio.TFT-LCD-Module -->
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
        <td style="border: none; text-align: right;">
            <h3>Motor</h3>
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
    <tr>
        <td style="border: none; text-align: left;">
            <img src="/Images/Display.webp" alt="Display" style="max-width: 100%;">
        </td>
        <td style="border: none; text-align: right;">
            <img src="/Images/L293DArduinoShieldPinouts.png" alt="L293D Motor Driver Shield" style="max-width: 100%;">
        </td>
    </tr>
</table>

<h3>ADC analog-to-digital converter</h3>
<p>it is connected to pin A8 or as number 62</p>
