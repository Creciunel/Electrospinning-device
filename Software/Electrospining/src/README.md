<h1>Project Structure</h1>
<h2>Main Files</h2>
<ol>
    <li><strong>main.cpp</strong>: Here the <code>setup()</code> function and <code>loop()</code> function are defined, initializing all tasks and starting the main program.</li>
</ol>

<h2>Modules</h2>
<ol>
    <li><strong>adc.h/adc.cpp</strong>: The ADC (Analog-to-Digital Converter) module handles voltage measurement and manages semaphores for accessing ADC data.</li>
    <li><strong>display.h/display.cpp</strong>: The Display module is responsible for displaying information on a connected screen.</li>
    <li><strong>motor.h/motor.cpp</strong>: The Motor module controls the motors and interacts with them.</li>
</ol>

<h2>Main Functions</h2>
<ol>
    <li><strong>displayTask()</strong>: This function is responsible for displaying information on the screen.</li>
    <li><strong>voltageMeasureTask()</strong>: This function handles voltage measurement using the ADC and semaphores for synchronized access to data.</li>
    <li><strong>motorsTask()</strong>: This function controls the motors and interacts with them.</li>
</ol>