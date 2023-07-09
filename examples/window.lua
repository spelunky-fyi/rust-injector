meta.name = "Window test"
meta.version = "WIP"
meta.description = ""
meta.author = "Dregu"

local inputtext = ''
local inputnumber = 0
local inputslider = 6
local inputdrag = 9
local inputcombo = 1
local comboopts = { 'one', 'two', 'three' }
local inputcheck = false

local inputtooltip = 'This input\'s value is used as its tooltip.'

local widgetopen = true
local closebutton = false

local seedinput = ''
local widgetopen2 = false
local closebutton2 = false

-- load image to use later
local loadingimage = create_image('loading.png')

-- add a simple button to options to open our cluttered test windows
register_option_button('open', 'Open test window', function()
    widgetopen = true
end)
register_option_button('open2', 'Open seed dialog', function()
    widgetopen2 = true
end)

set_callback(function(draw_ctx)
    if closebutton then
        closebutton = false
        widgetopen = false
        message('Window was closed with a button')
    end
    if widgetopen then
        -- create a new window and test most of the widgets
        -- we'll put this one top center and make it movable, with no titlebar
        widgetopen = draw_ctx:window('##TestWindow', -0.3, 0.9, 0.6, 0.5, true, function(ctx, pos, size)
            draw_ctx:win_separator_text('Section One')

            draw_ctx:win_text(string.format("Geometry: %f,%f %f x %f", pos.x, pos.y, size.x, size.y))

            draw_ctx:win_width(0.12)
            draw_ctx:win_input_text('Width < 1.0 means the fraction of the window width', '')

            draw_ctx:win_width(-0.12)
            draw_ctx:win_input_text('I\'m short', 'Negative width means width of the description instead')

            draw_ctx:win_width(100)
            fixedwidth = draw_ctx:win_input_text('Fixed width textbox knows it only takes 12 characters', fixedwidth and fixedwidth:sub(0, 12) or '')

            -- open another window from this window
            if draw_ctx:win_button('Open seed dialog') then
                widgetopen2 = true
            end

            -- all the input widgets return the current value always, and expect you to keep feeding it back, or it will just revert to default when you blur the input
            local stupidexample = draw_ctx:win_input_text('Not like this', '') -- this will just always be empty

            -- you need to circulate your value through the widget like this
            inputtext = draw_ctx:win_input_text('Write text##texthereplease', inputtext)
            inputnumber = draw_ctx:win_input_int('Write number', inputnumber)
            inputslider = draw_ctx:win_slider_int('Select number##slider', inputslider, 1, 10)
            inputdrag = draw_ctx:win_drag_float('Select another number##drag', inputdrag, 1, 10)
            inputcombo = draw_ctx:win_combo('Combo thing', inputcombo, table.concat(comboopts, '\0')..'\0\0')
            inputcheck = draw_ctx:win_check('Check this out', inputcheck)

            draw_ctx:win_separator_text('Section Two')
            -- pseudo table layout
            do
                -- four columns
                local n = 4
                local width = 1 / n
                local headers = {'Alpha', 'Beta', 'Gamma', 'Delta'}
                -- headers
                for i=1,n do
                    if i > 1 then draw_ctx:win_sameline(width*(i-1), 4) end
                    draw_ctx:win_text(headers[i])
                end
                -- textboxes with no label
                for i=1,n do
                    if i > 1 then draw_ctx:win_sameline(0, 4) end
                    draw_ctx:win_width(width)
                    whatever = draw_ctx:win_input_text(F'##BoxA{i}', whatever or '')
                end
                -- more textboxes with no label
                for i=1,n do
                    if i > 1 then draw_ctx:win_sameline(0, 4) end
                    draw_ctx:win_width(width)
                    whatever = draw_ctx:win_input_text(F'##BoxB{i}', whatever or '')
                end
            end
            draw_ctx:win_text('Click here:')
            draw_ctx:win_inline()
            if draw_ctx:win_button('Submit') then
                message(inputtext..' '..tostring(inputnumber)..' '..tostring(inputslider)..' '..tostring(inputdrag)..' '..comboopts[inputcombo]..' '..tostring(inputcheck))
            end

            -- long text is wrapped
            draw_ctx:win_text('Sed non justo eu orci lacinia mollis. Morbi finibus luctus massa eu gravida. Maecenas ornare tincidunt pellentesque. Aliquam vel nulla eu mauris pulvinar consequat sed vitae nisi. Nulla facilisi. Nulla venenatis mollis mauris, sed blandit nisi auctor facilisis. In tempor magna eleifend, ornare sem in, egestas massa. Donec pulvinar orci ac ligula rhoncus, a hendrerit elit interdum. Maecenas sed orci quis justo imperdiet finibus.')

            -- add tooltips to widgets
            draw_ctx:win_text('Hover the cursor over this text to see a tooltip.')
            draw_ctx:win_tooltip('This is a tooltip for the text.')
            draw_ctx:win_button('This button has a tooltip too')
            draw_ctx:win_tooltip('This is a tooltip for the button.\nTooltips can have multiple lines.')
            inputtooltip = draw_ctx:win_input_text('Tooltip text input', inputtooltip)
            draw_ctx:win_tooltip(inputtooltip)

            -- draw the image we loaded before
            if loadingimage > -1 then
                draw_ctx:win_image(loadingimage, 0, 0)

                -- imagebutton, always 1/3 width of window, height smaller but keeps 3:1 aspect ratio
                draw_ctx:win_imagebutton('##coolbutton', loadingimage, 0.33, 0.11, 0, 0, 1, 1)
            end

            -- remember to use unique labels on identical inputs
            if draw_ctx:win_button('Test##FirstTest') then
                message('First button')
            end
            if draw_ctx:win_button('Test##SecondTest') then
                message('Second button')
            end

            -- or distinguish between identical inputs with pushid (integer)
            a = {}
            for i=1,5 do
                draw_ctx:win_pushid(i)
                a[i] = draw_ctx:win_button('A')
                if i < 5 then
                    draw_ctx:win_inline()
                end
                draw_ctx:win_popid()
            end
            for i=1,5 do
                if a[i] then
                    message('Clicked A number '..tostring(i))
                end
            end

            -- or with pushid (string)
            local b_ids = { "first", "second", "third" }
            b = {}
            for i, id in ipairs(b_ids) do
                draw_ctx:win_pushid(id)
                b[id] = draw_ctx:win_button('B')
                if i < #b_ids then
                    draw_ctx:win_inline()
                end
                draw_ctx:win_popid()
            end
            for _, id in ipairs(b_ids) do
                if b[id] then
                    message('Clicked B string '..id)
                end
            end

            closebutton = draw_ctx:win_button('Close window')

            -- circle the player, but only inside this window
            if #players > 0 then
                local x, y, l = get_position(players[1].uid)
                local sx, sy = screen_position(x, y)
                radius = screen_distance(1) -- one tile
                draw_ctx:draw_layer(DRAW_LAYER.WINDOW)
                draw_ctx:draw_circle(sx, sy, radius, 3, rgba(255, 0, 0, 255))
            end

        end)
        if not widgetopen then
            message('Window was closed from the X')
        end
    end

    -- another smaller thing opened from the larger thing
    if closebutton2 then
        closebutton2 = false
        widgetopen2 = false
    end
    if widgetopen2 then
        -- non movable prompt in the center of your screen
        widgetopen2 = draw_ctx:window('Enter seed', 0, 0, 0, 0, false, function()
            seedinput = draw_ctx:win_input_text('Seed', seedinput)
            local seed = tonumber(seedinput, 16)
            if draw_ctx:win_button('Set seed') and seed then
                closebutton2 = true
                set_seed(seed)
            end
        end)
    end
end, ON.GUIFRAME)
