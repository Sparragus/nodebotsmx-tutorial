var express = require('express');
var app = express();

var twitterAPI = require('twitter');
var twitter = new twitterAPI({
  consumer_key: 'consumer_key',
  consumer_secret: 'consumer_secret',
  access_token_key: 'access_token_key',
  access_token_secret: 'access_token_secret'
});

var tweetCount = 0;
var hashtag = '#food';

app.get('/', function(req, res) {
  res.send('Count: ' + tweetCount);
  console.log('Tweet count: ' + tweetCount);
  tweetCount = 0;
});

twitter.stream('statuses/filter', {track: hashtag}, function(stream) {
  stream.on('data', function(tweet) {
    console.log(tweet);
    tweetCount+=1;
  });
});

app.listen(process.env.PORT || 3000, function(){
  console.log('Express server listening on port 3000');
});