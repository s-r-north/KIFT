// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.js                                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: scollet <marvin@42.fr>                     +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/07 13:10:04 by scollet           #+#    #+#             //
//   Updated: 2017/10/07 13:59:09 by scollet          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

/* This just works */
/* EDIT : this may be a little broken */

var record = require('node-record-lpcm16')
var fs = require('fs')

var file = fs.createWriteStream('./src/client/audio/test4.wav', { encoding: 'binary' })

record.start({
  sampleRate: 44100,
  verbose: true
}).pipe(file)

// Stop recording after three seconds
setTimeout(function () {
  record.stop()
  process.exit()
}, 10000)
