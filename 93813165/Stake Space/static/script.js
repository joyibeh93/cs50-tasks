function validateSignUpForm() {
    var name = document.getElementById("name").value;
    var email = document.getElementById("email").value;
    var pass = document.getElementById("pass").value;
    var re_pass = document.getElementById("re_pass").value;

    if (name === "" || email === "" || pass === "" || re_pass === "") {
        alert("Please fill in all fields");
        return false;
    }

    return true;
}

function validateSignInForm() {
    var your_name = document.getElementById("your_name").value;
    var your_pass = document.getElementById("your_pass").value;

    if (your_name === "" || your_pass === "") {
        alert("Please fill in all fields");
        return false;
    }

    return true;
}
