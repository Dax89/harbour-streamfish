.pragma library

var urlregex = new RegExp("[-a-zA-Z0-9@:%._\\+~#=]{1,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");
var hostportregex = new RegExp("[-a-zA-Z0-9@:%._\\+~#=]{1,256}:[0-9]+");
var ipregex = new RegExp("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
var ipportregex = new RegExp("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}:[0-9]+");

function isUrl(url) {
    return urlregex.test(url) || ipregex.test(url) || ipportregex.test(url) || hostportregex.test(url);
}
