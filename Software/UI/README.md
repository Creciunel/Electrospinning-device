<h2>Description of UI</h2>
<p>This section contains a project with a desktop Windows app for communication via UART from a computer to an electrospinning device based on an Arduino Mega or ATmega2560 microcontroller.</p>

<h3>Steps for Using the Device and Protocol</h3>
<ul>
    <li>The app has a dropdown menu for viewing and selecting available COM ports.</li>
    <li>It also has a button to connect to the device and informs us if the connection was successful or if the connection was lost.</li>
    <li>There is a window where we can see the voltage, one for motor speed, and the last one for time (actual/necessary for the process), and all the parameters can also be adjusted.</li>
    <li>The protocol sends messages in the format: <i><b>status, start/stop, voltage, speed, time.</b></i> When the device is working, we have two values for time: one is the total time needed for the experiment and the other is the actual time in the process.</li>
    <li>There are also two buttons for starting and stopping the process.</li>
    <li>The protocol looks like this: <i>1,1,9000,50,60,3</i>. If the process is not running, then the last value of the status state is false (0).</li>
    <li>If there is a problem, the message will start with <b>0</b>, which means errors, and that will be an error message such as: <i>0, TFT display error</i>.</li>
</ul>

<h3>Communication</h3>
<p>Additionally, the application also sends messages to the execution, such as the processing time or speed.</p>
<p>The format is <i>key-value</i> with <code>s1</code> or <code>m10</code>.</p>
<table>
    <tr>
        <th>Key</th>
        <th>Value</th>
    </tr>
    <tr>
        <td><code>s</code></td>
        <td>1 or 0</td>
    </tr>
    <tr>
        <td><code>m</code></td>
        <td>0 to 100 or more</td>
    </tr>
    <tr>
        <td><code>n</code></td>
        <td>0 to 100 or more</td>
    </tr>
    <tr>
        <td><code>t</code></td>
        <td>0 to 100 or more</td>
    </tr>
</table>
<ul>
    <li><code>s</code> - comes from start/stop</li>
    <li><code>m</code> - comes from motor speed</li>
    <li><code>n</code> - comes from motor numbers of revolution</li>
    <li><code>t</code> - comes from time</li>
</ul>