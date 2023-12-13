let sendBtn = document.getElementById('send');
let reachOut=document.getElementById('reach')
sendBtn.addEventListener('click', function(){
    // alert('I will get back to you shortly');
    reachOut.textContent=`I will get back to you shortly `
     // Function to clear the text after 5 seconds
     setTimeout(function() {
        reachOut.textContent = 'Get in Touch with Me !';
    }, 5000); // 5000 milliseconds = 5 seconds

})
