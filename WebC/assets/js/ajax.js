var port;
port = parseInt(window.location.toString().split(':')[window.location.toString().split(':').length - 1]);

function getXMLHttpRequest() {
	var xhr = null;

	if (window.XMLHttpRequest || window.ActiveXObject) {
		if (window.ActiveXObject) {
			try {
				xhr = new ActiveXObject("Msxml2.XMLHTTP");
			} catch(e) {
				xhr = new ActiveXObject("Microsoft.XMLHTTP");
			}
		} else {
			xhr = new XMLHttpRequest();
		}
	} else {
		alert("Votre navigateur ne supporte pas l'objet XMLHTTPRequest...");
		return null;
	}
	return xhr;
}


function request(callback, arg, mode) {
	var xhr = getXMLHttpRequest();

	xhr.onreadystatechange = function() {
		if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 0)) {
      if (mode == 1) {
			     callback(xhr.responseText);
      } else if (mode == 2) {
   		   callback(xhr.responseText);
      }
		}
	};

  if (port) {
    xhr.open("GET", "http://localhost:" + port + "/exec?arg=" + arg, true);
    xhr.send(null);
  } else {
    alert("Aucun port n'a été spécifier\nImpossible de comuniquer");
  }
}

function readQuit(data) {
  if (data == 'quit') {
    var newWin = window.open("", "_self");
    newWin.document.write("Merci de fermer l'onglet");
    newWin.close();
  }
}

function readData(data) {
	console.log(data);
}

$(window).keydown(function(event) {
	if (event.keyCode == 27) {
		$("#bg-white").css('display', 'none');
	}
});

function updateEnv() {
	var nom = this.id.substr(6);
	var env = $(this).parent()[0].innerText;
	env = env.substr(0, env.length - 1);
	var p_env = env.split('=', 2);

	$("#bg-white").css('display', 'block');
	$("#nameUpdateEnv").keydown(false);
	$("#nameUpdateEnv").val(p_env[0]);
	$("#valUpdateEnv").val(p_env[1]);
}

function delEnv() {
	var xhr = getXMLHttpRequest();
	var name = this.id.substr(6);
	xhr.onreadystatechange = function() {
		if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 0)) {
				if (xhr.responseText == "del_env_ok") {
					request(readEnv, 'get_env', 2);
				}
			}
		};
	if (port) {
		xhr.open("GET", "http://localhost:" + port + "/exec?arg=del_env&nom=" + encodeURIComponent(name), true);
		xhr.send(null);
	} else {
		alert("Aucun port n'a été spécifier\nImpossible de comuniquer");
	}
	return (false);
}

function get_name_env(str) {
	var i;
	var ret = "";

	for (i = 0; i < str.length && str[i] != '='; i++) {
		ret += str[i];
	}
	return (ret);
}

function readEnv(data) {
  var doc = document.getElementById("listEnv");
  doc.innerHTML = "";
  var json = JSON.parse(data);

  if (json.length != 0) {
    for (var i = 0; i < json.length; i++) {
			var p = document.createElement("p");
			var br = document.createElement("br");
			var update = document.createElement("span");
			update.className = "fa fa-pencil update-env"
			update.id = "update" + get_name_env(json[i]);

			var del = document.createElement("span");
			del.className = "fa fa-trash-o del-env";
			del.id = "delete" + get_name_env(json[i]);

      var node = document.createElement("span");
      node.innerHTML = json[i];

			node.appendChild(update);
			node.appendChild(del);
			node.appendChild(br);
			p.appendChild(node);
      doc.appendChild(p);
			$(del).click(delEnv);
			$(update).click(updateEnv);
    }
  } else {
      var p = document.createElement("p");
      p.innerHTML = "Il n'y a pas de variable d'environement";
      doc.appendChild(p);
  }
}

$(document).ready(function() {
	$("#addEnv").click(function(){
		var nom = $("#nameAddEnv").val();
		var val = $("#valAddEnv").val();
		for (var i = 0; i < nom.length; i++) {
			if ("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_".indexOf(nom[i]) == -1) {
				alert('Le nom ne doit contenir que des caractéres alphanumérique');
				return ;
			}
		}
		var xhr = getXMLHttpRequest();
		xhr.onreadystatechange = function() {
			if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 0)) {
					if (xhr.responseText == "add_env_ok") {
						$("#nameAddEnv").val("");
						$("#valAddEnv").val("");
						request(readEnv, 'get_env', 2);
					}
				}
			};
		if (port) {
			xhr.open("GET", "http://localhost:" + port + "/exec?arg=add_env&nom=" + encodeURIComponent(nom) + "&val=" + encodeURIComponent(val), true);
			xhr.send(null);
		} else {
			alert("Aucun port n'a été spécifier\nImpossible de comuniquer");
		}
		return false;
	});

	$("#updateEnv").click(function() {
		var nom = $("#nameUpdateEnv").val();
		var val = $("#valUpdateEnv").val();

		var xhr = getXMLHttpRequest();
		xhr.onreadystatechange = function() {
			if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 0)) {
					if (xhr.responseText == "update_env_ok") {
						$("#nameUpdateEnv").val("");
						$("#valUpdateEnv").val("");
						$("#bg-white").css('display', 'none');
						request(readEnv, 'get_env', 2);
					}
				}
			};
		if (port) {
			xhr.open("GET", "http://localhost:" + port + "/exec?arg=update_env&nom=" + encodeURIComponent(nom) + "&val=" + encodeURIComponent(val), true);
			xhr.send(null);
		} else {
			alert("Aucun port n'a été spécifier\nImpossible de comuniquer");
		}
		return false;
	});
});

request(readEnv, 'get_env', 2);
