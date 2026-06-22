 #pragma once
const char HTML[] PROGMEM = R"GEARUP(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Gear Up 31242 Claw</title>
<style>
@import url('https://fonts.googleapis.com/css2?family=Orbitron:wght@700;900&family=Rajdhani:wght@500;600;700&display=swap');
*,*::before,*::after{box-sizing:border-box;margin:0;padding:0;}
:root{
 --bg:#080808;--panel:#111;--panel2:#161616;--border:#1f1f1f;
 --gold:#c9a84c;--gold-hi:#f5d76e;--gold-dim:#3a2e10;
 --silver:#c8d0d8;--text:#e0ddd5;--muted:#505050;
}
body{background:var(--bg);color:var(--text);font-family:'Rajdhani',sans-serif;min-height:100vh;display:flex;flex-direction:column;align-items:center;padding-bottom:3rem;}
/* TOPBAR */
.topbar{width:100%;background:linear-gradient(180deg,#181818,#0f0f0f);border-bottom:1px solid var(--border);padding:1.1rem 1.6rem;display:flex;align-items:center;gap:1.1rem;margin-bottom:1.8rem;position:relative;overflow:hidden;}
.topbar::after{content:'';position:absolute;bottom:0;left:0;right:0;height:2px;background:linear-gradient(90deg,transparent 0%,var(--gold-dim) 20%,var(--gold) 50%,var(--gold-dim) 80%,transparent 100%);}
.logo-ring{width:58px;height:58px;border-radius:50%;border:2px solid var(--gold);padding:4px;background:radial-gradient(circle at 40% 35%,#2a2200,#080808);box-shadow:0 0 0 3px #111,0 0 16px rgba(201,168,76,0.15);flex-shrink:0;}
.logo-ring img{width:100%;height:100%;object-fit:contain;border-radius:50%;}
.topbar-info{flex:1;}
.topbar-info h1{font-family:'Orbitron',sans-serif;font-weight:900;font-size:1.15rem;letter-spacing:0.1em;background:linear-gradient(90deg,#f5d76e 0%,#c9a84c 50%,#c8d0d8 100%);-webkit-background-clip:text;-webkit-text-fill-color:transparent;background-clip:text;line-height:1.1;}
.topbar-info p{font-size:0.65rem;font-weight:600;letter-spacing:0.22em;color:var(--muted);text-transform:uppercase;margin-top:3px;}
.topbar-info p span{color:var(--gold);}
.topbar-badge{font-family:'Orbitron',sans-serif;font-size:0.6rem;font-weight:700;letter-spacing:0.1em;color:var(--gold);background:var(--gold-dim);border:1px solid var(--gold);border-radius:4px;padding:3px 7px;white-space:nowrap;}
/* SECTION LABEL */
.section-label{width:100%;max-width:500px;padding:0 1rem;margin-bottom:0.4rem;display:flex;align-items:center;gap:0.7rem;}
.section-label span{font-family:'Orbitron',sans-serif;font-size:0.58rem;font-weight:700;letter-spacing:0.2em;color:var(--muted);text-transform:uppercase;white-space:nowrap;}
.section-label::after{content:'';flex:1;height:1px;background:var(--border);}
/* CONTROLS */
.controls{display:flex;flex-direction:column;gap:0.9rem;width:100%;max-width:500px;padding:0 1rem;}
/* CARD */
.card{background:var(--panel);border:1px solid var(--border);border-radius:12px;padding:1.3rem 1.5rem;position:relative;transition:border-color 0.15s,box-shadow 0.15s;}
.card-shine{position:absolute;top:0;left:1.5rem;right:1.5rem;height:1px;background:linear-gradient(90deg,transparent,var(--gold),transparent);opacity:0.15;transition:opacity 0.15s;border-radius:1px;}
.card.active{border-color:var(--gold);box-shadow:0 0 18px rgba(201,168,76,0.08);}
.card.active .card-shine{opacity:0.8;}
.card-top{display:flex;justify-content:space-between;align-items:center;margin-bottom:1rem;}
.card-meta{display:flex;flex-direction:column;gap:3px;}
.lbl{font-family:'Orbitron',sans-serif;font-size:0.68rem;font-weight:700;letter-spacing:0.18em;color:var(--gold);}
.ch{font-size:0.65rem;font-weight:600;color:var(--muted);letter-spacing:0.1em;}
.angle{font-family:'Orbitron',sans-serif;font-size:2.1rem;font-weight:900;color:var(--silver);line-height:1;}
.angle sup{font-size:0.8rem;color:var(--muted);vertical-align:super;font-weight:500;}
input[type=range]{-webkit-appearance:none;appearance:none;width:100%;height:3px;border-radius:2px;background:var(--border);outline:none;cursor:pointer;margin-bottom:0.5rem;}
input[type=range]::-webkit-slider-thumb{-webkit-appearance:none;appearance:none;width:22px;height:22px;border-radius:50%;background:var(--gold);border:2px solid var(--gold-hi);margin-top:-9.5px;cursor:pointer;transition:transform 0.1s,background 0.1s;}
input[type=range]:active::-webkit-slider-thumb{transform:scale(1.3);background:var(--silver);border-color:#fff;}
.ticks{display:flex;justify-content:space-between;color:var(--muted);font-size:0.58rem;font-weight:600;letter-spacing:0.04em;}
/* FOOTER */
.footer{background:var(--panel);border:1px solid var(--border);border-radius:12px;padding:1rem 1.5rem;display:flex;align-items:center;justify-content:space-between;gap:1rem;width:100%;max-width:500px;margin:0.9rem 1rem 0;}
.status{display:flex;align-items:center;gap:0.5rem;font-size:0.72rem;font-weight:600;color:var(--muted);flex:1;min-width:0;}
.status span{overflow:hidden;text-overflow:ellipsis;white-space:nowrap;}
.dot{width:7px;height:7px;border-radius:50%;background:var(--gold);flex-shrink:0;animation:pulse 2s ease-in-out infinite;}
@keyframes pulse{0%,100%{opacity:1}50%{opacity:0.15}}
.btn{font-family:'Rajdhani',sans-serif;font-size:0.8rem;font-weight:700;letter-spacing:0.12em;text-transform:uppercase;background:transparent;border:1px solid var(--gold);color:var(--gold);padding:0.45rem 1.2rem;border-radius:7px;cursor:pointer;transition:background 0.15s,color 0.15s;white-space:nowrap;flex-shrink:0;}
.btn:hover{background:var(--gold);color:#080808;}
.btn:active{background:var(--silver);border-color:var(--silver);color:#080808;}
</style>
</head>
<body>


<div class="topbar">
 <div class="logo-ring"><img src="/logo" alt="Gear Up"></div>
 <div class="topbar-info">
   <h1>GEAR UP</h1>
   <p>FTC Team <span>#31242</span> &nbsp;&middot;&nbsp; Claw Master</p>
 </div>
 <div class="topbar-badge">4-SERVO</div>
</div>


<div class="section-label"><span>Rotation &amp; Joints</span></div>


<div class="controls">


 <div class="card" id="cBase">
   <div class="card-shine"></div>
   <div class="card-top">
     <div class="card-meta"><div class="lbl">BASE</div><div class="ch">CH 3 &mdash; Rotation</div></div>
     <div class="angle"><span id="nBase">90</span><sup>&deg;</sup></div>
   </div>
   <input type="range" min="0" max="180" value="90" id="sBase" oninput="mv('Base',this.value)" onchange="snd('Base',this.value)">
   <div class="ticks"><span>0&deg;</span><span>45&deg;</span><span>90&deg;</span><span>135&deg;</span><span>180&deg;</span></div>
 </div>


 <div class="card" id="cLower">
   <div class="card-shine"></div>
   <div class="card-top">
     <div class="card-meta"><div class="lbl">LOWER JOINT</div><div class="ch">CH 0 &mdash; Inverted</div></div>
     <div class="angle"><span id="nLower">90</span><sup>&deg;</sup></div>
   </div>
   <input type="range" min="0" max="180" value="90" id="sLower" oninput="mv('Lower',180-this.value)" onchange="snd('Lower',180-this.value)">
   <div class="ticks"><span>180&deg;</span><span>135&deg;</span><span>90&deg;</span><span>45&deg;</span><span>0&deg;</span></div>
 </div>


 <div class="card" id="cArm">
   <div class="card-shine"></div>
   <div class="card-top">
     <div class="card-meta"><div class="lbl">ARM</div><div class="ch">CH 1</div></div>
     <div class="angle"><span id="nArm">90</span><sup>&deg;</sup></div>
   </div>
   <input type="range" min="0" max="180" value="90" id="sArm" oninput="mv('Arm',this.value)" onchange="snd('Arm',this.value)">
   <div class="ticks"><span>0&deg;</span><span>45&deg;</span><span>90&deg;</span><span>135&deg;</span><span>180&deg;</span></div>
 </div>


 <div class="card" id="cClaw">
   <div class="card-shine"></div>
   <div class="card-top">
     <div class="card-meta"><div class="lbl">CLAW</div><div class="ch">CH 2</div></div>
     <div class="angle"><span id="nClaw">90</span><sup>&deg;</sup></div>
   </div>
   <input type="range" min="0" max="180" value="90" id="sClaw" oninput="mv('Claw',this.value)" onchange="snd('Claw',this.value)">
   <div class="ticks"><span>0&deg;</span><span>45&deg;</span><span>90&deg;</span><span>135&deg;</span><span>180&deg;</span></div>
 </div>


</div>


<div class="footer">
 <div class="status"><div class="dot"></div><span id="st">Connected &mdash; GearUp-Arm</span></div>
 <button class="btn" onclick="ca()">Center All</button>
</div>


<script>
var mv=function(n,v){document.getElementById('n'+n).textContent=v;var p=(parseInt(document.getElementById('s'+n).value)/180)*100;document.getElementById('s'+n).style.background='linear-gradient(to right,#c9a84c '+p+'%,#1f1f1f '+p+'%)';document.getElementById('c'+n).classList.add('active');};
var snd=function(n,v){document.getElementById('c'+n).classList.remove('active');fetch('/set?servo='+n+'&angle='+v).then(function(){document.getElementById('st').textContent=n+' → '+v+'°';}).catch(function(){document.getElementById('st').textContent='⚠ Connection lost';});};
var ca=function(){['Base','Lower','Arm','Claw'].forEach(function(n){document.getElementById('s'+n).value=90;mv(n,90);snd(n,90);});};
mv('Base',90);mv('Lower',90);mv('Arm',90);mv('Claw',90);
</script>
</body>
</html>
)GEARUP";



