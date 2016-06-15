.pragma library

function replaceSimpleTag(s, tag) {
    var startoldtag = "[" + tag  + "]", endoldtag = "[/" + tag + "]";
    var starttag = "<" + tag + ">", endtag = "</" + tag + ">";

    return s.replace(startoldtag, starttag).replace(endoldtag, endtag);
}

function replaceColorTag(s, tag, cap) {
    var startoldtag = "[" + tag + " " + cap[2] + "]", endoldtag = "[/" + tag + "]";
    var starttag = "<font color='" + cap[2] + "'>", endtag = "</font>";

    return s.replace(startoldtag, starttag).replace(endoldtag, endtag);
}

var tagdispatcher = {
    "COLOR": replaceColorTag,
    "B": replaceSimpleTag,
    "I": replaceSimpleTag,
}

function parse(s) {
    var cap = /\[(\w+)\s*(\w*)\].*\[\/\1\]/.exec(s);

    while(cap && cap[1])
    {
        var tag = cap[1].toUpperCase();
        var tagcallback = tagdispatcher[tag];

        if(tagcallback) {
            s = tagcallback(s, cap[1], cap);
            return parse(s);
        }

        console.log("Unsupported Tag: '" + tag + "'");
    }

    return s;
}
