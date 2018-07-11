// Setting timer
$(".formBtn.addTime").click(function () {
    $("#timeVal").val(parseInt($("#timeVal").val()) + parseInt($(this).text()));
});

$(".formBtn.set").click(function () {
    $.ajax("/time?min=" + $("#timeVal").val())
        .done(function (data) {
            if (data.success) {
                $("#msg").text(data.msg).show()
            }
        });
});

// Slider
$(".slider").on('input', _throttle(function () {
    $.ajax("/dim?val=" + $(this).val())
        .done(function (data) {
            if (data.success) {
                $("#msg").text(data.msg).show()
            }
        });
}, 40));

// Dim Buttons
$("#dimUp").click(function () {
    $.ajax("/dimup")
        .done(function (data) {
            console.log(data);
        });
})

$("#dimDown").click(function () {
    $.ajax("/dimdown")
        .done(function (data) {
            console.log(data);
        });
})

// ON/OFF
$("#onOff").click(function () {
    $.ajax("/toggle")
        .done(function (data) {
            if (data.success) {
                $("#msg").text(data.msg).show()
            }
        });
})

// Popup messages
$("#msg").click(function () {
    $("#msg").hide();
})


/*******************
 * Utility functions
 *******************/

/**
 * Debouncing function
 * @param {Function} func Function to throttle
 * @param {Integer} delay millisecond to wait before accepting a value
 */
function _debounce(func, delay) {
    let inDebounce
    return function () {
        const context = this
        const args = arguments
        clearTimeout(inDebounce)
        inDebounce = setTimeout(function () { func.apply(context, args) }, delay);
    }
}

/**
 * Throttling function
 * @param {Function} func Function to throttle
 * @param {Integer} limit time interval in millisecinds in which to accept the latest value
 */
function _throttle(func, limit) {
    let lastFunc
    let lastRan
    return function () {
        const context = this
        const args = arguments
        if (!lastRan) {
            func.apply(context, args)
            lastRan = Date.now()
        } else {
            clearTimeout(lastFunc)
            lastFunc = setTimeout(function () {
                if ((Date.now() - lastRan) >= limit) {
                    func.apply(context, args)
                    lastRan = Date.now()
                }
            }, limit - (Date.now() - lastRan))
        }
    }
}