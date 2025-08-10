const express = require('express');
const {getShortUrl} = require('./shortUrl');

const app =express();
// write your code here
app.get('/:shortUrl', (req, res) => {
    // write your code here
    getShortUrl(req.params.shortUrl);
    res.send('Short URL is: ' + req.params.shortUrl);
});

app.listen(3000, () => {
    console.log('Server is running at port 3000');
});