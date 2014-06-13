/**
 * @const
 */
var RPC_DELAY_MS = 250

var sk = {};

/**
 * @constructor
 */
sk.net = function() {
  /**
   * @field
   * @private
   */
  sk.net.timer = null;

  /**
   * @field
   * @private
   */
  sk.net.destinationUrl = null;

  /**
   * @field
   * @private
   */
  sk.net.websock = null;

  /**
   * @field
   * @private
   */
  sk.net.xmlHttp = (window.XMLHttpRequest)
      ? new XMLHttpRequest()
      : new ActiveXObject("Microsoft.XMLHTTP");

  /**
   * @method
   * @private
   */
  sk.net.rpcCallback = function() {
    if (sk.net.xmlHttp.readyState == 4) {
      sk.content.setHtml(sk.net.xmlHttp.responseText);
    }
  }

  /**
   * @method
   * @private
   */
  sk.net.sendSearchNow = function() {
    sk.net.xmlHttp.open("GET", sk.net.destinationUrl, true);
    sk.net.xmlHttp.onreadystatechange = sk.net.rpcCallback;
    sk.net.xmlHttp.send(null);
  }

  /**
   * @method
   * @public
   */
  sk.net.sendSearch = function(searchQuery) {
    sk.net.destinationUrl = "search?query=" + escape(searchQuery);
    if (sk.net.timer != null) {
      clearTimeout(sk.net.timer);
    }
    sk.net.timer = setTimeout(sk.net.sendSearchNow, RPC_DELAY_MS);
  }

  sk.net.initWebSocket = function(callback) {
    sk.net.websock = new WebSocket("ws://localhost:8080/ws");
    sk.net.websock.onmessage = callback;
  }
}

var margin = {top: 20, right: 40, bottom: 30, left: 20},
    width = 760 - margin.left - margin.right,
    height = 500 - margin.top - margin.bottom,
    barWidth = Math.floor(width / 19) - 1;

var x = d3.scale.linear()
    .range([barWidth / 2, width - barWidth / 2]);
    x.domain([1,20]);

var y = d3.scale.linear()
    .range([height, 0]);
    y.domain([0, 10000]);

var yAxis = d3.svg.axis()
    .scale(y)
    .orient("right")
    .tickSize(-width)
    .tickFormat(function(d) { return Math.round(d / 1e6) + "M"; });

// An SVG element with a bottom-right origin.
var svg = d3.select("#container").append("svg")
    .attr("width", width + margin.left + margin.right)
    .attr("height", height + margin.top + margin.bottom)
  .append("g")
    .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

// A sliding container to hold the bars by birthyear.
var rankeditems = svg.append("g")
    .attr("class", "rankeditems");

var timeTick = 1;

// A label for the current year.
var title = svg.append("text")
    .attr("class", "title")
    .attr("dy", ".71em")
    .text("Time: " + timeTick);

svg.append("g")
    .attr("class", "y axis")
    .attr("transform", "translate(" + width + ",0)")
    .call(yAxis)
  .selectAll("g")
  .filter(function(value) { return !value; })
    .classed("zero", true);

var rankeditem = rankeditems.selectAll(".rankeditem")
    .data(d3.range(1, 20, 1))
  .enter().append("g")
    .attr("class", "rankeditem")
    .attr("id", function(rank) {return "item-" + rank;})
    .attr("transform", function(rank) { return "translate(" + x(rank) + ",0)"; });

rankeditem.selectAll("rect")
   .data([1, 2, 3])
  .enter().append("rect")
    .attr("x", -barWidth / 2)
    .attr("width", barWidth)
    .attr("y", y)
    .attr("height", function(rank) {  return y(rank); });

rankeditem.append("text")
    .attr("y", height + 14)
    .text("label");


var currData;

sk.net();
sk.net.initWebSocket(function(evt) {
   currData = eval(evt.data);
   var i = 0;
   var max = 0;
   for (i =1; i <= 20; ++i) {
     var val = currData[i] ? currData[i][1] : 0;
     if (val > max) max = val;
   }
   for (i =1; i <= 20; ++i) {
     var val = currData[i] ? currData[i][1] : 0;
     var val2 = currData[i] ? currData[i][2] : 0;
     var val3 = currData[i] ? currData[i][3] : 0;
     var element = document.getElementById("item-" + i).firstChild;
     var element2 = element.nextSibling;
     var element3 = element2.nextSibling;
     element3.nextSibling.innerHTML = currData[i] ? currData[i][0] : "";

     var hgt = (max > height) ? (val * height / max) : val;
     var hgt2 = (max > height) ? (val2 * height / max) : val2;
     var hgt3 = (max > height) ? (val3 * height / max) : val3;
     
     if (element)
       element.setAttribute("height", hgt);
       element.setAttribute("y", height - hgt);
       element2.setAttribute("height", hgt2);
       element2.setAttribute("y", height - hgt2);
       element3.setAttribute("height", hgt3);
       element3.setAttribute("y", height - hgt3);

   }
});
