var release = false;

function var_dump(e)
{
    if (release == false)
	console.log(JSON.stringify(e));
}

function appMessageUpdate(e)
{
    if (e.payload["dummy"] != "order")
    {
	var_dump("you ordered a " + e.payload["dummy"] + " for the Dragon");
    }
    else
	Pebble.sendAppMessage({0: 0});
}

Pebble.addEventListener("appmessage", appMessageUpdate);
