const my_button = document.getElementById("my_button")
const input_ip  = document.getElementById("ip")
const sendBtn   = document.getElementById("sendBtn")
const refreshBtn   = document.getElementById("refreshBtn")
const msg       = document.getElementById("msg")
const xhr = new XMLHttpRequest()
const xhr_dim = new XMLHttpRequest()
const form = document.getElementById("objectsForm")

const move = (q, d) => {
    console.log("move", q, d)
    xhr.open("POST", "/move", true)
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded")
    xhr.send(`q=${q}&d=${d < 0 ? "n" : "p"}`)
}

const refresh = () => {
  DetectedObjects.deleteButtons(); // Elimino los botones que se crearon antes
  UserCanvas.updateBackground();

  xhr.open('POST', '/detect-objects', true)
  xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded")
  xhr.send("")
  refreshBtn.disabled = true

  xhr.onreadystatechange = () => {
    if (xhr.readyState === XMLHttpRequest.DONE){
        if (xhr.status === 200){
          detectedObjects = JSON.parse(xhr.response);
          DetectedObjects.createButtons(detectedObjects);
        };
    };
  };
  refreshBtn.disabled = false             
}
my_button.onclick = () => {
    xhr.open("POST", "/connect", true)
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded")
    xhr.send("ip=" + input_ip.value)
}

xhr.onreadystatechange = () => {
    if (xhr.readyState === XMLHttpRequest.DONE) {
        sendBtn.disabled = false

        if (xhr.status === 200) {
            if (xhr.response === "connected") {
                requestDimensions()

                alert("Conectado")
            } else if (xhr.response === "end_draw") {
                msg.innerText = "Finalizó 😁"
            } else {
                console.log(xhr.response)
            }
        }
    }
}

function requestDimensions() {
    xhr_dim.open("POST", "/dim", true)
    xhr_dim.setRequestHeader("Content-Type", "application/x-www-form-urlencoded")
    xhr_dim.send("")
    
    xhr_dim.onreadystatechange = () => {
        if (xhr_dim.readyState === XMLHttpRequest.DONE) {
            if (xhr_dim.status === 200) {
                const [width, height] = xhr_dim.response.split("|")
                UserCanvas.setDimensions(parseFloat(width), parseFloat(height))
            }
        }
    }
}

const base = 13.4
const altura = 10.00
const minRadius = 3.3
const maxRadius = 14.92
UserCanvas.init()

sendBtn.onclick = () => {
    if (UserCanvas.isObjectSelected()) {
        xhr.open("POST", "/draw", true)
        xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded")
        xhr.send("q=3&ps=" + UserCanvas.toString())

        msg.innerText = "Moviendo..."
        sendBtn.disabled = true
    } else {
        alert("Se debe seleccionar un objeto")
    }
}
