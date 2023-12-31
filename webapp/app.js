const express = require("express")
const bodyParser = require("body-parser")
const app = express()
const axios = require("axios")

let robotIp = '192.168.0.1'

// Configuramos express para usar a body-parser como middleware
app.use(bodyParser.urlencoded({ extended: true }))

app.listen(3000, () => {
    console.log("Aplicación iniciada y escuchando en puerto 3000")
})

// para las css estáticas
app.use(express.static(__dirname))

app.get("/", (req, res) => {
    res.sendFile(__dirname + "/index.html")
})

app.post("/connect", (req, res) => {
    if (req.body) {
        robotIp = req.body.ip
        axios({
            method: "get",
            url: `http://${robotIp}/connect`,
            timeout: 5000
        })
            .then(r => {
                console.log("Connect: " + r.status)
                res.end("connected")
            })
            .catch(error => res.end(error.code))
    } else {
        res.end("Falta IP")
    }
})

app.post("/detect-objects", (req, res) => {
  axios({
      method: "get",
      url: `http://${robotIp}/detect-objects`,
      timeout: 5000
  })
    .then(r => {
      if (r.status === 200)
          console.log(r.data);
          res.setHeader('Content-Type', 'application/json');
          res.end(JSON.stringify(r.data));
  })
  .catch(error => res.end(error.code))
})

app.post("/dim", (req, res) => {
    axios({
        method: "get",
        url: `http://${robotIp}/dim`,
        timeout: 5000
    })
        .then(r => {
            if (r.status === 200)
                res.end(r.data)
        })
        .catch(error => res.end(error.code))
})

app.post("/draw", (req, res) => {
    console.log("Sending: [" + req.body.q + "] " + req.body.ps)
    axios
        .get(`http://${robotIp}/draw`, {params: {q: req.body.q, ps: req.body.ps}})
        .then(res_a => {
            console.log(`Status: ${res_a.status}`)
            res.end("end_draw")
        })
        .catch(err => {
            console.error(err)
        })
})

app.post("/move", (req, res) => {
    if (req.body) {
        console.log(`m${req.body.q}${req.body.d}`)
        axios({
            method: "get",
            url: `http://${robotIp}/m${req.body.q}${req.body.d}`,
            timeout: 5000
        })
            .then(r => {
                console.log("Connect: " + r.status)
                res.end("connected")
            })
            .catch(error => res.end(error.code))
    } else {
        res.end("Falta IP")
    }
})

app.get('/capture.jpg', async (req, res) => {
    try {
        // Make a GET request to the external endpoint to get the image
        const response = await axios.get('http://192.168.0.1/capture.jpg', {
            responseType: 'stream'
        });

        res.set('Content-Type', 'image/jpeg');
        response.data.pipe(res);

    } catch (error) {
        console.log(error);
        res.status(500).send('Internal Server Error');
    }
});
