const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<title>www.sribalaji.eu.org</title>
</head>
<style>
@import url('https://fonts.googleapis.com/css2?family=Google+Sans:wght@400;500;700&display=swap');

* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

body {
  background: url('https://images.unsplash.com/photo-1549778399-f94fd24d4697?ixlib=rb-4.0.3&ixid=M3wxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8fA%3D%3D&auto=format&fit=crop&w=1074&q=80') no-repeat center center fixed;
  background-size: cover;
  font-family: Montserrat, Arial, sans-serif;
}

h2{
  font-size:14px;
}
.widget{
  box-shadow:0 40px 10px 5px rgba(0,0,0,0.4);
  margin:100px auto;
  height: 330px;
  position: relative;
  width: 500px;
}
 
.upper{
  border-radius:5px 5px 0 0;
  background: linear-gradient(to bottom, #f5f5f5, #e1e1e1);
  height:200px;
  padding:20px;
}
 
.date{
  font-size:40px;
}
.year{
  font-size:30px;
  color:#c1c1c1;
}
.place{
  color:#222;
  font-size:40px;
}
.lower{
  background:#00A8A9;
  border-radius:0 0 5px 5px;
  font-family:'Advent Pro';
  font-weight:200;
  height:130px;
  width:100%;
}
.clock{
  background:#00A8A9;
  border-radius:100%;
  box-shadow:0 0 0 15px #f5f5f5,0 10px 10px 5px rgba(0,0,0,0.3);
  height:150px;
  position:absolute;
  right:25px;
  top:-35px;
  width:150px;
}
 
.hour{
  background:#f5f5f5;
  height:50px;
  left:50%;  
  position: absolute;
  top:25px;
  width:4px;
}
 
.min{
  background:#f5f5f5;
  height:65px;
  left:50%;  
  position: absolute;
  top:10px;
  transform:rotate(100deg);
  width:4px;
}
 
.min,.hour{
  border-radius:5px;
  transform-origin:bottom center;
  transition:all .5s linear;
}
 
.infos{
  list-style:none;
}
.info{
  color:#fff;
  float:left;
  height:100%;
  padding-top:10px;
  text-align:center;
  width:25%;
}
.info span{
  display: inline-block;
  font-size:40px;
  margin-top:20px;
}
.weather p {
  font-size:20px;padding:10px 0;
}
.anim{animation:fade .8s linear;}
 
@keyframes fade{
  0%{opacity:0;}
  100%{opacity:1;}
}
 
a{
 text-align: center;
 text-decoration: none;
 color: white;
 font-size: 15px;
 font-weight: 500;
}

/* Floating Letters Animation */
.floating-letters {
  position: absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
}

.floating-letters span {
  font-size: 36px;
  font-weight: bold;
  color: #fff;
  opacity: 0;
  animation-name: floating-letters;
  animation-duration: 2s;
  animation-iteration-count: infinite;
  animation-timing-function: ease-in-out;
}

@keyframes floating-letters {
  0% {
    transform: translate(-50%, -50%);
    opacity: 0;
  }
  50% {
    transform: translate(-50%, -60%);
    opacity: 1;
  }
  100% {
    transform: translate(-50%, -50%);
    opacity: 0;
  }
}
</style>
<body>
 
<div class="widget"> 
  <div class="clock">
    <div class="min" id="min"></div>
    <div class="hour" id="hour"></div>
  </div>
  <div class="upper">
    <div class="date" id="date">21 March</div>
    <div class="year">Temperature</div>
    <div class="place update" id="temperature">23 &deg;C</div>
  </div>
  <div style="text-align: center;"><a href="https://www.sribalaji.eu.org" style="align:center">www.sribalaji.eu.org</a></div>
  <div class="lower">    
    <ul class="infos">
      <li class="info temp">
        <h2 class="title">TEMPERATURE</h2>
        <span class='update' id="temp">21 &deg;C</span>
      </li>
      <li class="info weather">
        <h2 class="title">PRESSURE</h2>
        <span class="update" id="pressure">0 mb</span>
      </li>
      <li class="info wind">
        <h2 class="title">RAIN</h2>
        <span class='update' id="rain">0%</span>
      </li>
      <li class="info humidity">
        <h2 class="title">HUMIDITY</h2>
        <span class='update' id="humidity">23%</span>
      </li>
    </ul>
  </div>
</div>
 
<script>
setInterval(drawClock, 2000);

function drawClock() {
  var now = new Date();
  var hour = now.getHours();
  var minute = now.getMinutes();
  var second = now.getSeconds();

  // Date
  var options = { year: 'numeric', month: 'long', day: 'numeric' };
  var today = new Date();
  document.getElementById("date").innerHTML = today.toLocaleDateString("en-US", options);

  // Hour
  var hourAngle = (360 * (hour / 12)) + ((360 / 12) * (minute / 60));
  var minAngle = 360 * (minute / 60);
  document.getElementById("hour").style.transform = "rotate(" + hourAngle + "deg)";
  // Minute
  document.getElementById("min").style.transform = "rotate(" + minAngle + "deg)";

  // Get Temperature, Humidity, and Pressure Data
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var data = JSON.parse(this.responseText);
      var temperature = data.temperature;
      var humidity = data.humidity;
      var pressure = data.pressure;

      // Update temperature, humidity, and pressure values
      document.getElementById("temp").innerHTML = temperature + " &deg;C";
      document.getElementById("humidity").innerHTML = humidity + "%";
      document.getElementById("pressure").innerHTML = pressure + " mb";

      // Additional functionality
      if (temperature > 30) {
        document.getElementById("temp").style.color = "red";
      } else if (temperature < 10) {
        document.getElementById("temp").style.color = "blue";
      } else {
        document.getElementById("temp").style.color = "white";
      }

      if (humidity > 70) {
        document.getElementById("humidity").style.color = "blue";
      } else {
        document.getElementById("humidity").style.color = "white";
      }
    }
  };
  xhttp.open("GET", "readBMP", true);
  xhttp.send();
  
  // Function to map a value from one range to another
  function mapRange(value, minInput, maxInput, minOutput, maxOutput) {
  return (value - minInput) * (maxOutput - minOutput) / (maxInput - minInput) + minOutput;
}

}
</script>
</body>
</html>
)=====";
