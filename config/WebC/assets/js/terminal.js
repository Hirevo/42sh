$(document).ready(function() {
  var validcmd = localStorage.length;
  var historynb = localStorage.length;

	$("#terminalCore").click(function() {
    console.log(localStorage);
    console.log(historynb);
		$("#terminalInput").focus();
		document.getElementById("terminalInput").selectionStart = $("#terminalInput").val().length;
    document.getElementById("terminalInput").selectionEnd = $("#terminalInput").val().length;
	});
	$("#terminalInput").click(function() {
		if (this.selectionStart <= 3) {
			this.selectionStart = 3;
      this.selectionEnd = 3;
		}
	});

  $("#terminalInput").keyup(function(e) {
    if (e.keyCode != 13) {
      if (localStorage.getItem(historynb + "")) {
        localStorage.setItem(historynb + "", $("#terminalInput").val().substr(3));
      } else if (e.key.length == 1) {
        localStorage.setItem(historynb + "", $("#terminalInput").val().substr(3));
      }
      if ($("#terminalInput").val().substr(3).length == 0) {
        localStorage.removeItem(historynb + "");
      }
    }
  });
	$("#terminalInput").keydown(function(e) {
    if (e.key == "ArrowUp" || e.key == "ArrowDown") {
      if (e.key == "ArrowUp") {
        if (historynb > 0) {
          historynb -= 1;
          $("#terminalInput").val("$> " + localStorage.getItem(historynb + ""));
        }
      }
      if (e.key == "ArrowDown") {
        if (historynb < localStorage.length - 1) {
          historynb += 1;
          $("#terminalInput").val("$> " + localStorage.getItem(historynb + ""));
        } else if (historynb == localStorage.length - 1 && historynb < validcmd) {
          historynb += 1;
          $("#terminalInput").val("$> ");
        }
      }
      return (false);
    }
    if (e.key == "Home") {
      this.selectionStart = 3;
			this.selectionEnd = 3;
      return (false);
    }
    if (e.key == "End") {
      this.selectionStart = $(this).val().length;
      this.selectionEnd = $(this).val().length;
      return (false);
    }
		if (e.keyCode == 38) {
			this.selectionStart = 3;
			this.selectionEnd = 3;
			return (false);
		}
		if (this.selectionStart <= 3 && (e.keyCode == 8 || e.keyCode == 37)) {
			return (false);
		}
		if (this.selectionStart < 3) {
			return (false);
		}

		if (e.keyCode == 13) {
			var cmd = $("#terminalInput").val().substr(3);
			var xhr = getXMLHttpRequest();
			xhr.onreadystatechange = function() {
				if (xhr.readyState == 4 && (xhr.status == 200 || xhr.status == 0)) {
            $("#terminalInput").val("$> ");
            validcmd += 1;
            historynb += 1;
            $("#terminalCore").val(xhr.responseText);
            $("#terminalCore").scrollTop(99999999);
					}
				};
			if (port) {
				xhr.open("GET", "http://localhost:" + port + "/exec?arg=exec&cmd=" + encodeURIComponent(cmd), true);
				xhr.send(null);
			} else {
				alert("Aucun port n'a été spécifier\nImpossible de comuniquer");
			}
			return (false);
		}
	});
});
